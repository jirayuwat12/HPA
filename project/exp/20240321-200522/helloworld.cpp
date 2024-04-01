#include <omp.h>
#include <stdio.h>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

vector<vector<int> > G;

bool check_cover(const vector<bool> &comb){
    int ans = 0;

    for(int i = 0; i < comb.size(); i++){
        bool connected = false;
        for (int j = 0; j < comb.size(); j++){
            if(G[i][j] == 1 && comb[j]){
                connected = true;
                break;
            }
        }
        if (!connected){
            ans++;
        }
    }
    return ans == 0;
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

    vector<bool> comb(v, false);

    for(int i = v-1; i >= 0; i--){
        comb[i] = true;

        do{
            if(check_cover(comb)){
                for(int j = 0; j < v; j++){
                    printf("%d", comb[j] ? 1 : 0);
                }
                return 0;
            }
        }while(next_permutation(comb.begin(), comb.end()));
        comb[i] = false;
    }
}