#include <omp.h>
#include <stdio.h>
#include <vector>
#include <map>
#include <algorithm>
#include <stdint.h>

using namespace std;

vector<vector<int> > G;

bool check_cover(const int64_t &comb){
    int ans = 0;

    for(int i = 0; i < G[0].size(); i++){
        bool connected = false;
        for (int j = 0; j < G[0].size(); j++){
            if(G[i][j] == 1 && (comb & (1<<j))){
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

    int v, e;
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
        for(int64_t comb = 1; comb <= (1<<v); comb++){
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
    }
}