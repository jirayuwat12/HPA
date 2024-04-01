#include <stdio.h>
#include <omp.h>
#include <time.h>

int main(void){
    int a[100000];
    long stime, etime;
    // not use openmp omp function
    stime = time(NULL);

    #pragma omp parallel for
    for(int i=0; i<100000; i++){
        a[i] = 2*i+i;
        printf("a[%d], %d\n", i, a[i]);
    }

    etime = time(NULL);
    printf("Time: %ld\n", etime-stime);

    return 0;
}

// compile with: gcc -fopenmp openmp.c -o openmp.exe