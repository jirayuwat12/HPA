# !/bin/bash

# get file name
file_name=$1

# run 5 iterations
for i in {1..5}
do
    echo "Iteration $i"
    g++ -o $file_name $file_name.cpp
    time ./$file_name
done
