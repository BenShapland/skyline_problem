#!/bin/bash

echo "Running Benchmarking Script for CPU Parallel"

if [[ $# -eq 3 ]]; then
    size=$1
    num_core=$2
    num_instance=$3
else
    echo "Using Default Values"
    size=5000
    num_core=6
    num_instance=1000
fi

hold=0

for ((i=0;i<$num_instance;i++))
do
    hold=$(./parallel bench $size $num_core $i |grep time | awk '{print $2}')
    echo "Running Instance $i --> Time: $hold us"
    let "total=total + hold"
    
done

# echo $total
echo "Average Time:"$((total /num_instance ))" us"
# collect all the times and sum/ by count
echo "size: $size"
echo "number of cores: $num_core"


