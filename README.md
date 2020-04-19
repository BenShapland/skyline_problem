# skyline_problem
[Pareto optimality](https://en.wikipedia.org/wiki/Pareto_efficiency) is a concept that originated in Economics to describe a game theoretic strategy that *dominates* all alternatives; i.e., no matter the circumstances, it is the best choice. Many data analysis tasks can also be thought of as game theoretic; e.g., selecting a product from an online shop/aggregator (such as Amazon or Skyscanner) is a game theoretic problem of determining the best trade-off of quality and price relative to an adversary (the retailer or service provider) who is also involved in the transaction but has the opposing pay-off. [The skyline problem](http://delab.csd.auth.gr/papers/IISA2015tpm.pdf) is to select all the points from a dataset that offer the maximisation of *some* trade-off. Depending on the amount of correlation in the data, it can reduce reduce a dataset to just a few points or only by half.

Google doc links for developers referance

Interm Report 1 - editable from link
https://docs.google.com/document/d/18KMW_xI_nk4Zgqg8r5NLPR1Y1j5IeWIYuVQxi610P9s/edit?usp=sharing

Interm Report 2 - editable from link
https://docs.google.com/document/d/1zMy0XRLxMfB9fp2gygNS8Z-aWCYBne-WlXbtq5mYruY/edit?usp=sharing

Interm Report 3 -editable from link
https://docs.google.com/document/d/1vfb0J7DKYIZbsff4Bv4xABI0F8F69pzvHiN-EvvkPpY/edit?usp=sharing

Plan of attack for iterm 3 -GPGPU
https://docs.google.com/document/d/1NvzulK7GovufvcqnaPSh3plWleHjxywzH7YsHhJpAIg/edit?usp=sharing

BAD copy:
https://docs.google.com/document/d/1YMiDLCQd3QnpE150zXRuKwICiOqGe3Sxm3DOrDqNndQ/edit?usp=sharing


## Running the code 
ANY PREREQUIRED COMMANDS to give permitions could be here
First cd into the working directory.

### Single Core
There are 3 solutions for single core: AoS, SoA Basic, and SoA_XY. All 3 of these solutions can be benchmarked. Only SoA_XY can be compared the multi core solutions.
Single core benchmarking. First open the single core directory.
```
cd Single\ Core/
```
Now open the folder you want to test AoS, SoA Basic, and SoA_XY:
##### Array of Structures(AoS)
```
cd AoS\ Single\ Core/ 
make -B aos  
./aos 
 ```
 **Optionaly:** *./aos 10* can be run with any number, the number is the number of nodes in the data sets used for benchmarking.
##### Structure of Arrays Basic
```
cd SoA\ Basic/
make -B soa  
./soa 
 ```
**Optionaly:** *./soa 10* can be run with any number, the number is the number of nodes in the data sets used for benchmarking.
##### Structure of Arrays XY Combined 
```
cd SoA\ XY
make solution
```
The command bellow is for **benchmarking**.
```
./solution bench
```
**Optionaly:** *./solution bench 10 3* can be run with any numbers, 10 is the number of nodes in the data sets used for benchmarking and 3 is the number of times a test is ran.

The command bellow is for **comparing** out puts with multi core and GPU solutions.
```
./solution compare
``` 
**Optionaly:** *./solution compare 1000 2* can be run with any numbers, 1000 is the number of nodes in the data sets and 2 is the seed used to generate those nodesn. To compare outputs it is important to use the same number of nodes and seed.

The defult values used in compare equivalent across all solutions, this means that the outputs should be equivalent. 

### Multi Core
Multi core benchmarking. First open the multi core directory and make the files.
```
cd Parallel
make parallel
 ```
The command bellow is for **benchmarking**.
```
./benchmark.sh
```
**Optionaly:** *./benchmark.sh 1000 6 50 * can be run with any numbers, 1000 is the number of nodes in the data sets used for benchmarking and 50 is the number of times a test is ran and 6 is the number of cores used.

The command bellow is for **comparing** out puts with multi core and GPU solutions.
```
./parallel compare
``` 
**Optionaly:** *./solution compare 1000 6 2* can be run with any numbers, 1000 is the number of nodes in the data sets and 2 is the seed used to generate those nodesn and 6 is the number of cores used. To compare outputs it is important to use the same number of nodes and seed.

The defult values used in compare equivalent across all solutions, this means that the outputs should be equivalent. 


 ### GPU  
 *N* is the size of the dataset, the number of nodes.
 *blocks* how many blocks you want to run in your solution.
 *threads* number of threads spawned per block.
 
 **Note:**  *N* should equal to *blocks* multiplied by *threads*. Example: 4000 = 4 \* 1000 
 ```
 Example:
 make -B Solution N=4000 blocks=4 threads=1000
 ```
 In this example random seed is 5.
 ##### Constan Memory solution 
Constant memory is small there for the number *N* should not be greater then 69696969 depending on model of GPU.
 ```
 make -B gpuconstant N=4000 blocks=4 threads=1000
 ```
 The command bellow is for **benchmarking**.
```
 ./gpuconstant bench
```
**Optionaly:** *./gpuconstant bench 50* 50 is the number of times a test is ran.

The command bellow is for **comparing** out puts with multi core and GPU solutions.
```
./gpuconstant compare
``` 
**Optionaly:** *./gpuconstant compare 5* 5 is the seed used to generate those nodes. To compare outputs it is important to use the same number of nodes and seed.

The defult values used in compare equivalent across all solutions, this means that the outputs should be equivalent. 
 
 ##### Global Memory oplution
 *N* should not be greater then 69696969 depending on model of GPU.
  ```
 make -B gpuglobal N=4000 blocks=4 threads=1000
 ```
  The command bellow is for **benchmarking**.
```
 ./gpuglobal bench
```
**Optionaly:** *./gpuglobal bench 50* 50 is the number of times a test is ran.

The command bellow is for **comparing** out puts with multi core and GPU solutions.
```
./gpuglobal compare
``` 
**Optionaly:** *./gpuglobal compare 5* 5 is the seed used to generate those nodes. To compare outputs it is important to use the same number of nodes and seed.

The defult values used in compare equivalent across all solutions, this means that the outputs should be equivalent.
 
 ##### Shared Block Memory solution
 *N* should not be greater then 69696969 depending on model of GPU.
  ```
 make -B gpushared N=4000 blocks=4 threads=1000
 ```
   The command bellow is for **benchmarking**.
```
 ./gpushared bench
```
**Optionaly:** *./gpushared bench 50* 50 is the number of times a test is ran.

The command bellow is for **comparing** out puts with multi core and GPU solutions.
```
./gpushared compare
``` 
**Optionaly:** *./gpushared compare 5* 5 is the seed used to generate those nodes. To compare outputs it is important to use the same number of nodes and seed.

The defult values used in compare equivalent across all solutions, this means that the outputs should be equivalent.
 
 ##### Sort Based Manhatten Solution (NOT FINISHED)
This Sort based solution uses more global memmory then other solution there for the number *N* should not be greater then 69696969 depending on model of GPU.
  ```
 make -B gpuman N=4000 blocks=4 threads=1000
 ./gpuman 5
 ```
 ### Comparing Outputs of GPU solutions and CPU solutions
Although inputing a *random_seed* is optional it can generated data based on the number given. The ouput of each solution should be the same aslong as the *random_seed* is the same. The defult values used in compare equivalent across all solutions, this means that the outputs should be equivalent. Any differences in output may come from the fact that some solutions do not keep nodes that have the same XY values even if they have different names. All inputs of the CPU solutions should be contained in the GPU solutions. When doing sanity checks the XY values were printed.

**Helpful commands for further investigatio**
```
GPU:
nvprof 
cuda-memcheck
CPU:
perf stat
```


