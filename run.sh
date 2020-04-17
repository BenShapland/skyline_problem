#!/bin/sh

echo "Running Bash Script"
sed -i -e "s/#define N .*/#define N $1/g" $4
sed -i -e "s/#define num_blocks .*/#define num_blocks $2/g" $4
sed -i -e "s/#define num_thread_per_block .*/#define num_thread_per_block $3/g" $4
echo "N set to $1"
echo "num_blocks set to $2"
echo "num_thread_per_block set to $3"
echo "Compiling $4"
