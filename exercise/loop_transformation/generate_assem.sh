# generate assembly code for mat_mul.c for O1, O2, O3

gcc -O1 -S mat_mul.c -o mat_mul_O1.s
gcc -O2 -S mat_mul.c -o mat_mul_O2.s
gcc -O3 -S mat_mul.c -o mat_mul_O3.s

# show runtime of mat_mul.c for O1, O2, O3
gcc -O1 mat_mul.c -o mat_mul_O1
gcc -O2 mat_mul.c -o mat_mul_O2
gcc -O3 mat_mul.c -o mat_mul_O3

echo "O1"
time ./mat_mul_O1

echo "O2"
time ./mat_mul_O2

echo "O3"
time ./mat_mul_O3
