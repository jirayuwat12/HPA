int main(){
    int n = 500;
    int A[n][n], B[n][n], C[n][n];

    // matrix multiplication
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++){
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}