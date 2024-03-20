#include <stdio.h>

void add(int size, int *a,int *b) {
    for (int i=0;i<size;i++) {
        a[i] += b[i];
    }
}

int main() {
    int size = 100000;
    int a[size];
    int b[size];
    for (int i=0;i<size;i++) {
        a[i] = i;
        b[i] = size-i;
    }
    
    for (int i=0;i<size;i++)
        add(size,a,b);

    printf("Done!\n");
    return 0;
}