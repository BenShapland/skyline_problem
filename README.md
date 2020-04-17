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
```
ex:
cd Single\ Core
```
then run the make file,

### CPU 
#### Single Core
Single core benchmarking. First open the single core directory.
```
cd Single\ Core/
```
Now open the folder you want to test Array of Structures(AoS) or Structure of Arrays hot/cold split(SOA):
##### Array of Structures(AoS)
```
cd AoS\ Single\ Core/
```
The command below is for benchmarking a brute force solution.
```
make -B aos  
./aos 
 ```
 **Optionaly:** *./aos 10* can be run with any number, the number is the number of nodes in the data sets used for benchmarking.
##### Structure of Arrays hot/cold split(SOA) 
```
cd SoA\ Hot\ and\ Cold/
```
The command below is for benchmarking two single core solutions, sort and brute force.
```
make -B soa  
./soa 
 ```
**Optionaly:** *./soa 10* can be run with any number, the number is the number of nodes in the data sets used for benchmarking.
#### Multi Core
Multi core benchmarking. First open the multi core directory.
```
cd Parallel/
 ```
The command below is for bench marking two single core solutions, sort and brute force. 
*N* is the size of the dataset, the number of nodes.
*num_ test_instances* is how many times the benchmark will run before it averages and returns the times. 
```
command number_of_nodes num_ test_instances
 ```
 ### GPU and comparing solutions  
 *N* is the size of the dataset, the number of nodes.
 *blocks* how many blocks you want to run in your solution.
 *threads* number of threads spawned per block.
 *random_seed* is an optianl number, it will generated data based on the number given. The ouput of each solution should be the same aslong as the *random_seed* is the same. 
 
 **Note:**  *N* should equal to *blocks* multiplied by *threads*. Example: 4000 = 4 \* 1000 
 ```
 Example:
 make -B Solution N=4000 blocks=4 threads=1000
 ./Solution 5
 ```
 In this example random seed is 5.
 ##### Constan Memory solution 
Constant memory is small there for the number *N* should not be greater then 69696969 depending on model of GPU.
 ```
 make -B gpuconstant N=4000 blocks=4 threads=1000
 ./gpuconstant 5
 
 ```
 ##### Global Memory oplution
 *N* should not be greater then 69696969 depending on model of GPU.
  ```
 make -B gpuglobal N=4000 blocks=4 threads=1000
 ./gpuglobal 5
 ```
 ##### Shared Block Memory solution
 *N* should not be greater then 69696969 depending on model of GPU.
  ```
 make -B gpushared N=4000 blocks=4 threads=1000
 ./gpushared 5
 ```
 ##### Sort Based Manhatten Solution
This Sort based solution uses more global memmory then other solution there for the number *N* should not be greater then 69696969 depending on model of GPU.
  ```
 make -B gpuman N=4000 blocks=4 threads=1000
 ./gpuman 5
 ```
 ### Comparing Outputs of GPU solutions and CPU solutions
Although inputing a *random_seed* is optional it can generated data based on the number given. The ouput of each solution should be the same aslong as the *random_seed* is the same. Running the command bellow will give the output of the multi core solution and the SoA single core solution.

**Note:** The outputs on this command may be diffrent from the GPU because it does not always keep nodes that have the same value but different names. All outputs from the command should be included in the outputs of the commands above given that the same *random_seed* was used.

```
make cpu
./cpu <num_data_points> <num_cores> <random_integer_seed>
Example:
./cpu 4000 6 5
```

**Helpful commands for further investigatio**
```
GPU:
nvprof 
cuda-memcheck
CPU:
perf stat
```


