# skyline_problem
[Pareto optimality](https://en.wikipedia.org/wiki/Pareto_efficiency) is a concept that originated in Economics to describe a game theoretic strategy that *dominates* all alternatives; i.e., no matter the circumstances, it is the best choice. Many data analysis tasks can also be thought of as game theoretic; e.g., selecting a product from an online shop/aggregator (such as Amazon or Skyscanner) is a game theoretic problem of determining the best trade-off of quality and price relative to an adversary (the retailer or service provider) who is also involved in the transaction but has the opposing pay-off. [The skyline problem](http://delab.csd.auth.gr/papers/IISA2015tpm.pdf) is to select all the points from a dataset that offer the maximisation of *some* trade-off. Depending on the amount of correlation in the data, it can reduce reduce a dataset to just a few points or only by half.

Final write up:
https://docs.google.com/document/d/1WLd197xFtyKdnmmia2AAZh7e1-xdOruQfvQ64WeN9Rg/edit?usp=sharing


## Running the code 
First cd into the working directory.

### Single Core
There are 3 solutions for single core: AoS, SoA Basic, and SoA XY. All 3 of these solutions can be benchmarked. The output of SoA XY can also be comapred with other solutions.
First open the Single Core directory.
```
cd Single\ Core/
```
Now open the folder you want to test: AoS, SoA Basic, or SoA XY:
##### Array of Structures(AoS)
```
cd AoS\ Single\ Core/ 
make aos  

 ```
 **Optionally:** *./aos 10*  can pass in 1 argument *number_of_nodes* in the dataset
##### Structure of Arrays Basic
```
cd SoA\ Basic/
make soa  
./soa 
 ```
**Optionally:** *./soa 10*  can pass in 1 argument *number_of_nodes* in the dataset
##### Structure of Arrays XY Combined 
```
cd SoA\ XY
make solution
```
The command below is for **benchmarking**.
```
./solution bench
```
**Optionally:** *./solution bench 10 3*  can pass 2 arguments: *number_of_nodes* in the dataset and *num_test_run*.

The command below is for **comparing** outputs with other solutions based on a specific. 
```
./solution compare
``` 
**Optionally:** *./solution compare 1000 2*  can pass 2 arguments: *number_of_nodes* in the dataset and *seed*.
 

### MultiCore
Multicore benchmarking. First open the multicore directory and compile the files using the makefile. A bash file is provided to benchmark the solution. 
```
cd Parallel
make parallel
 ```
The command below is for **benchmarking**.
```
./benchmark.sh
```
**Optionally:** *./benchmark.sh 1000 6 50* can pass in 3 arguments:, *number_of_nodes* in the dataset used for benchmarking, number of cores *num_cores* and *num_test_run*.

The command below is for **comparing** outputs with multicore and GPU solutions.
```
./parallel compare
``` 
**Optionally:** *./solution compare 1000 6 2*  can pass in 3 arguments: *number_of_nodes* in the dataset used for benchmarking, number of cores *num_cores* and *seed*.

 ### GPU  
 *N* is the size of the dataset, the number of nodes. Default is 5000
 *blocks* how many blocks you want to run in your solution. Default is 5
 *threads* number of threads spawned per block. Default is 1000

 
 **Note:**  *N* MUST be equal to *blocks* multiplied by *threads*. Example: 4000 = 4 \* 1000 
 ```
 Example:
 make -B Script N=4000 blocks=4 threads=1000
 ```

 ##### Constant Memory solution 
Constant memory is small there for the number *N* should not be greater than 5000.
 ```
 make -B gpuconstant N=4000 blocks=4 threads=1000
 ```
 The command below is for **benchmarking**.
```
 ./gpuconstant bench
```
**Optionally:** *./gpuconstant bench 50* can pass in 1 argument: *num_test_runs*

The command below is for **comparing** outputs with multicore and GPU solutions.
```
./gpuconstant compare
``` 
**Optionally:** *./gpuconstant compare 5* can pass in 1 argument: *seed*
 
 
 ##### Global Memory solution
 *N* should not be greater then 500000 depending on model of GPU.
  ```
 make -B gpuglobal N=4000 blocks=4 threads=1000
 ```
  The command below is for **benchmarking**.
```
 ./gpuglobal bench
```
**Optionally:** *./gpuglobal bench 50* can pass in 1 argument: *num_test_runs*

The command below is for **comparing** outputs with multicore and GPU solutions.
```
./gpuglobal compare
``` 
**Optionally:** *./gpuglobal compare 5* can pass in 1 argument: *seed*

 
 ##### Shared Block Memory solution
 *N* should not be greater then 600000 depending on model of GPU.
  ```
 make -B gpushared N=4000 blocks=4 threads=1000
 ```
   The command below is for **benchmarking**.
```
 ./gpushared bench
```
**Optionally:** *./gpushared bench 50* can pass in 1 argument: *num_test_runs*

The command below is for **comparing** outputs with multicore and GPU solutions.
```
./gpushared compare
``` 
**Optionally:** *./gpushared compare 5* can pass in 1 argument: *seed*

### Note 
1) To compare outputs it is important to use the same number of nodes and seed.
2) The default values across each solutions are the same. Therefore when benchmarking without any arguments passed in, the results should match.

 ### Comparing Outputs of GPU solutions and CPU solutions
Although inputing a *random_seed* is optional it can generated data based on the number given. The ouput of each solution should be the same aslong as the *random_seed* is the same. Any differences in output may come from the fact that some solutions do not keep nodes that have the same XY values even if they have different names. All inputs of the CPU solutions should be contained in the GPU solutions. When doing sanity checks the XY values were printed.

**Helpful commands for further investigatio**
```
GPU:
nvprof 
cuda-memcheck
CPU:
perf stat
```


