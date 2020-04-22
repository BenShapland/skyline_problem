# skyline_problem
[Pareto optimality](https://en.wikipedia.org/wiki/Pareto_efficiency) is a concept that originated in Economics to describe a game theoretic strategy that *dominates* all alternatives; i.e., no matter the circumstances, it is the best choice. Many data analysis tasks can also be thought of as game theoretic; e.g., selecting a product from an online shop/aggregator (such as Amazon or Skyscanner) is a game theoretic problem of determining the best trade-off of quality and price relative to an adversary (the retailer or service provider) who is also involved in the transaction but has the opposing pay-off. [The skyline problem](http://delab.csd.auth.gr/papers/IISA2015tpm.pdf) is to select all the points from a dataset that offer the maximisation of *some* trade-off. Depending on the amount of correlation in the data, it can reduce reduce a dataset to just a few points or only by half.

Final write up:
https://docs.google.com/document/d/1WLd197xFtyKdnmmia2AAZh7e1-xdOruQfvQ64WeN9Rg/edit?usp=sharing


## Single Core
There are 3 solutions for single core: AoS, SoA Basic, and SoA XY. All 3 of these solutions can be benchmarked. The output of SoA XY can also be comapred with other solutions.
First open the Single Core directory.
```
cd Single\ Core/
```
Now open the folder you want to test: AoS, SoA Basic, or SoA XY:
### Array of Structures(AoS)
```
cd AoS\ Single\ Core/ 
make aos  

 ```
 **Optionally:** *./aos 10*  can pass in 1 argument *number_of_nodes* in the dataset
### Structure of Arrays Basic(SoA)
```
cd SoA\ Basic/
make soa  
./soa 
 ```
**Optionally:** *./soa 10*  can pass in 1 argument *number_of_nodes* in the dataset
### Structure of Arrays XY Combined(SoA_XY)
```
cd SoA\ XY
make solution
```
**benchmarking:**
```
./solution bench
```
**Optionally:** *./solution bench 10 3*  can pass 2 arguments: *number_of_nodes* in the dataset and *num_test_run*.

**comparing:** 
```
./solution compare
``` 
**Optionally:** *./solution compare 1000 2*  can pass 2 arguments: *number_of_nodes* in the dataset and *seed*.
 

## MultiCore
Multicore benchmarking. First open the multicore directory and compile the files using the makefile. A bash file is provided to benchmark the solution. 
```
cd Parallel
make parallel
 ```
**benchmarking:**.
```
./benchmark.sh
```
**Optionally:** *./benchmark.sh 1000 6 50* can pass in 3 arguments:, *number_of_nodes* in the dataset used for benchmarking, number of cores *num_cores* and *num_test_run*.

**comparing:**
```
./parallel compare
``` 
**Optionally:** *./solution compare 1000 6 2*  can pass in 3 arguments: *number_of_nodes* in the dataset used for benchmarking, number of cores *num_cores* and *seed*.

 ## GPU  
 *N* is the size of the dataset, the number of nodes. Default is 5000
 *blocks* how many blocks you want to run in your solution. Default is 5
 *threads* number of threads spawned per block. Default is 1000

 **Note:**  The number of nodes(N), blocks and threads per block need to be passed 
            in at compile time by the makefile as followed:
```
 Example:
 make -B Script N=4000 blocks=4 threads=1000
 ```
 **Note:**  *N* MUST be equal to *blocks* multiplied by *threads*. Example: 4000 = 4 \* 1000 

### Constant Memory solution 
Constant memory is small there for the number *N* should not be greater than 5000.
 ```
 make -B gpuconstant N=4000 blocks=4 threads=1000
 ```
**benchmarking:**.
```
 ./gpuconstant bench
```
**Optionally:** *./gpuconstant bench 50* can pass in 1 argument: *num_test_runs*

**comparing:**
```
./gpuconstant compare
``` 
**Optionally:** *./gpuconstant compare 5* can pass in 1 argument: *seed*
 
 ### Global Memory solution
 *N* should not be greater then 500000 depending on model of GPU.
  ```
 make -B gpuglobal N=4000 blocks=4 threads=1000
 ```
**benchmarking:**.
```
 ./gpuglobal bench
```
**Optionally:** *./gpuglobal bench 50* can pass in 1 argument: *num_test_runs*

**comparing:** 
```
./gpuglobal compare
``` 
**Optionally:** *./gpuglobal compare 5* can pass in 1 argument: *seed*

 
 ### Shared Block Memory solution
 *N* should not be greater then 600000 depending on model of GPU.
  ```
 make -B gpushared N=4000 blocks=4 threads=1000
 ```
**benchmarking:**.
```
 ./gpushared bench
```
**Optionally:** *./gpushared bench 50* can pass in 1 argument: *num_test_runs*

**comparing:** 
```
./gpushared compare
``` 
**Optionally:** *./gpushared compare 5* can pass in 1 argument: *seed*

## Note 
1) To compare outputs it is important to use the same number of nodes and seed value.
2) The default values across each solutions are the same. Therefore when benchmarking without any arguments passed in, the results should match.

**Helpful commands for further investigatio**
```
GPU:
nvprof 
cuda-memcheck
CPU:
perf stat
```


