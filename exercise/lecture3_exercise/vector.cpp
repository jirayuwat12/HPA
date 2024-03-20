#include <stdio.h>

#include <arm_neon.h> // Include the header file for ARM NEON intrinsics

void add_neon(int size, int *a, int*b) {
    int i=0;
    for (;i<size;i+=4) {
        // load 128-bit chunks of each array
        int32x4_t av = vld1q_s32(&a[i]);
        int32x4_t bv = vld1q_s32(&b[i]);
        // add each pair of 32-bit integers in chunks
        int32x4_t result = vaddq_s32(av, bv);
            
        // store 128-bit chunk to a
        vst1q_s32(&a[i], result);
    }
    // clean up
    for(;i<size;i++) {
        a[i] += b[i];
    }
}

int main() {
    int size = 10000;
    int a[size];
    int b[size];
    for (int i=0;i<size;i++) {
        a[i] = i;
        b[i] = size-i;
    }
    
    for (int i=0;i<size;i++)
        add_neon(size,a,b);

    printf("Done!\n");
    return 0;
}