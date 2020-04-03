# skyline_problem
[Pareto optimality](https://en.wikipedia.org/wiki/Pareto_efficiency) is a concept that originated in Economics to describe a game theoretic strategy that *dominates* all alternatives; i.e., no matter the circumstances, it is the best choice. Many data analysis tasks can also be thought of as game theoretic; e.g., selecting a product from an online shop/aggregator (such as Amazon or Skyscanner) is a game theoretic problem of determining the best trade-off of quality and price relative to an adversary (the retailer or service provider) who is also involved in the transaction but has the opposing pay-off. [The skyline problem](http://delab.csd.auth.gr/papers/IISA2015tpm.pdf) is to select all the points from a dataset that offer the maximisation of *some* trade-off. Depending on the amount of correlation in the data, it can reduce reduce a dataset to just a few points or only by half.

Interm Report 1 - editable from link
https://docs.google.com/document/d/18KMW_xI_nk4Zgqg8r5NLPR1Y1j5IeWIYuVQxi610P9s/edit?usp=sharing

Interm Report 2 - editable from link
https://docs.google.com/document/d/1zMy0XRLxMfB9fp2gygNS8Z-aWCYBne-WlXbtq5mYruY/edit?usp=sharing

Plan of attack for iterm 3 -GPGPU
https://docs.google.com/document/d/1NvzulK7GovufvcqnaPSh3plWleHjxywzH7YsHhJpAIg/edit?usp=sharing

BAD copy:
https://docs.google.com/document/d/1YMiDLCQd3QnpE150zXRuKwICiOqGe3Sxm3DOrDqNndQ/edit?usp=sharing


### AoS

    Node.h
    solution.hpp
    bechmarking.cpp 
    timing.hpp
    original_node.cpp
  

### SoA-hot_and_cold_data_split

    Node.h
    solution.hpp
    bechmarking.cpp 
    timing.hpp
    original_node.cpp


### Parallel
    Solution
        Node.h
        solution.hpp
        bechmarking.cpp 
        timing.hpp
        original_node.cpp


    Test
        Test code for building parallize solution
        

### GPGPU_basic
    GPU
        data_generator.cpp
        Node.h
        data-sanity-check.hpp
        solution_cpu.cpp
        solution_gpu.cu

    Test
        Test code for building parallize solution
        Test code for GPU parallelization single block


#### Benchmarking:
```
cd GPGPU_basic/GPU
```
#### Generate test data
```
g++ data_generator.cpp -o data
./data <num_of_nodes>
 ```
#### Benchmark CPU version
 ```
g++ -Wall -O3 -std=c++17 -mavx -march=native -fopenmp solution_cpu.cpp -o sol_cpu
./sol_cpu
 ```
#### Benchmark GPU version
 ```
nvcc -O3 -o sol_gpu solution_gpu.cu
./sol_gpu
 ```

## Note

**solution_gpu.cu** needs to be configured before compiling
 ```
#define N 5048 //  num_blocks * num_thread_per_block 
#define num_blocks  5
#define num_thread_per_block  1024  
 ```
**num_blocks** is the number of nodes being used -> Number of nodes genrated by data_generator.cpp
**num_blocks** number blocks for GPU
**num_thread_per_block** number of threads per block

**num_blocks** * **num_thread_per_block**  must be equal to N
