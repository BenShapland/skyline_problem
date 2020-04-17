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
cd GPGPU_basic/GPU
```
then run the make file,
### CPU 
```
cd CPU
 ```
#### Single Core
Single core benchmarking. First open the single core directory.

```
cd Single\ Core/
```
Now open the folder you want to test Array of Structures(AoS) or Structure of Arrays hot/cold split(SOA):
```
cd AoS\ Single\ Core/
OR
cd SoA\ Hot\ and\ Cold/
```
The command below is for bench marking two single core solutions, sort and brute force. 
*number_of_nodes* is the size of the dataset.
*num_ test_instances* is how many times the benchmark will run before it averages and returns the times. 
```
command number_of_nodes num_ test_instances
 ```
#### Multi Core
Multi core benchmarking. First open the multi core directory.
```
cd Parallel/
 ```
The command below is for bench marking two single core solutions, sort and brute force. 
*number_of_nodes* is the size of the dataset.
*num_ test_instances* is how many times the benchmark will run before it averages and returns the times. 
```
command number_of_nodes num_ test_instances
 ```
 ### GPU and comparing solutions  
 *number_of_nodes* is the size of the dataset.
 *number_of_blocks* how many blocks you want to run in your solution.
 *number_of_threads* number of threads spawned per block.
 *random_seed* is an optianl number, it will generated data based on the number given. The ouput of each solution should be the same aslong as the *random_seed* is the same. 
 
 **Note:**  *number_of_nodes* should equal *number_of_blocks* x  *number_of_threads*.
 ```
 Name_of_solution number_of_nodes number_of_blocks number_of_threads
 ./Name_of_solution RANDOM SEED
 ```
 ##### Constan Memory solution 
Constant memory is small there for the number *number_of_nodes* should not be greater then 69696969 depending on model of GPU.
 ```
 command 
 ```
 ##### Global Memory oplution
 *number_of_nodes* should not be greater then 69696969 depending on model of GPU.
  ```
 command 
 ```
 ##### Shared Block Memory solution
 *number_of_nodes* should not be greater then 69696969 depending on model of GPU.
  ```
 command 
 ```
 ##### Sort Based Solution
This Sort based solution uses more global memmory then other solution there for the number *number_of_nodes* should not be greater then 69696969 depending on model of GPU.
  ```
 command 
 ```
 ### Comparing Outputs of GPU solutions and CPU solutions
Although inputing a *random_seed* is optional it can generated data based on the number given. The ouput of each solution should be the same aslong as the *random_seed* is the same. Running the command bellow will give the output of the multi core solution and the SoA single core solution.

**Note:** The outputs on this command may be diffrent from the GPU because it does not always keep nodes that have the same value but different names. All outputs from the command should be included in the outputs of the commands above given that the same *random_seed* was used.

```
CPU_solution number_of_nodes number_of_blocks number_of_threads
 ./Name_of_solution RANDOM SEED
```

**Helpful commands for further investigatio**
```
GPU:
nvprof 
cuda-memcheck
CPU:
perf stat
```


