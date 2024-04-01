#include <omp.h>
#include <stdio.h>
#include <vector>
#include <map>
#include <algorithm>
#include <stdint.h>

using namespace std;

vector<vector<int> > G;
int v, e;

bool check_cover(const int64_t &comb){
    int ans = 0;

    for(int i = 0; i < v; i++){
        bool connected = false;
        for (int j = 0; j < v; j++){
            if(G[i][j] == 1 && (comb & (1<<j))){
                connected = true;
                break;
            }
        }
        if(!connected) return false;
    }
    return true;
}
bool check_cover(const int64_t &comb_second, const int64_t &comb_first){
    for(int i = 0; i < v; i++){
        bool connected = false;

        for (int j = 0; j < 64; j++){
            bool first_condition = (comb_first & (1<<j));
            if((G[i][j] == 1) & (first_condition)){
                connected = true;
                break;
            }
        }
        if(!connected) return false;

        for (int j = 65; j < v; j++){
            bool second_condition = (comb_second & (1<<(j-64)));
            if((G[i][j] == 1) & (second_condition)){
                connected = true;
                break;
            }
        }
        if(!connected) return false;
    }
    return true;
}


int main(int argc, char **argv){
    char *input_file = argv[1];
    char *output_file = argv[2];
    freopen(input_file, "r", stdin);
    freopen(output_file, "w", stdout);

    scanf("%d", &v);
    scanf("%d", &e);

    G.resize(v, vector<int>(v, 0));

    for(int i = 0; i < e; i++){
        int a, b;
        scanf("%d %d", &a, &b);
        G[a][b] = 1;
        G[b][a] = 1;
    }

    if (e==0){
        // if there are no edges, print all vertices
        for(int i = 0; i < v; i++){
            printf("1");
        }
    }else if(e == (v*(v-1))/2){
        // fully connected graph
        for(int i = 1; i < v; i++){
            printf("0");
        }
        printf("1");
    }else if(v <= 68){
        // brute force + parallel
        int min_cover = 1000000;
        int64_t min_comb = 0;
        #pragma omp parallel for schedule(guided)
        for(int64_t comb = 1; comb < (1<<v); comb++){
            if(check_cover(comb)){
                int count = 0;
                for(int i = 0; i < v; i++){
                    if(comb & (1<<i)){
                        count++;
                    }
                }
                #pragma omp critical
                {
                    if(count < min_cover){
                        min_cover = count;
                        min_comb = comb;
                    }
                }
            }
        }
        for(int i = 0; i < v; i++){
            if(min_comb & (1<<i)){
                printf("1");
            }else{
                printf("0");
            }
        }
    }else if(v <= 128){
        int g_min_cover = 1000000;
        vector<int> g_min_comb(v, 0);

        // split into 2 parts
        // second part is a bitset from left to right 64 bits
        // first part concatenate with second part with (v-64) bits
        #pragma omp parallel for schedule(guided)
        for(int64_t comb_second = 0; comb_second < (1<<(v-64)); comb_second++){
            int min_cover = 1000000;
            vector<int> min_comb;
            for(int64_t comb_first = 0; comb_first <= INT64_MAX; comb_first++){
                if(check_cover(comb_second, comb_first)){
                    int count = 0;
                    for(int i = 0; i < v; i++){
                        if((i < 64 && comb_first & (1<<i)) || (i >= 64 && comb_second & (1<<(i-64)))){
                            count++;
                        }
                    }
                    if(count < min_cover){
                        min_cover = count;
                        min_comb = vector<int>(v, 0);
                        for(int i = 0; i < v; i++){
                            if((i < 64 && comb_first & (1<<i)) || (i >= 64 && comb_second & (1<<(i-64)))){
                                min_comb[i] = 1;
                            }
                        }
                    }
                }
            }
            #pragma omp critical
            {
                if(min_cover < g_min_cover){
                    g_min_cover = min_cover;
                    g_min_comb = min_comb;
                }
            }
        }
        for(int i = 0; i < v; i++){
            printf("%d", g_min_comb[i]);
        }
    }
}

/*
C:\Users\jiray\Desktop\HPA\project\PowerGrid\grid-100-180 C:\Users\jiray\Desktop\HPA\project\vtune_out.txt
*/