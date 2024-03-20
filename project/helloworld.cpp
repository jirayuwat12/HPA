#include <omp.h>
#include <stdio.h>
#include <vector>
#include <map>

using namespace std;

vector<vector<int> > G;


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
}