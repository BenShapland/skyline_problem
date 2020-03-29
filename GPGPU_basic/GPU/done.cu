
/**
 * Toy example porting a simd algorithm to CUDA for an NVIDIA GPU
 *
 * Calculates the average size of set of 3d vectors.
 * Example input: {{1,1,1},{2,2,2}}
 * I.e., 1 vector of size (3*1^2)^-0.5 and 1 vector of size (3*2^2)^0.5
 * Example output: ( sqrt(3) + sqrt(12) ) / 2 = 2.59808
 */
#include <iostream>
#include <vector>

#include "Node.h"
#include "test-data.hpp"


#include <random> 	// std::rand, std::srand, std::default_random_engine
std::string random_string(std::size_t length)
{

    const std::string characters = "abcdefghijklmnopqrstuvwxyz";

    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(0, characters.size() - 1);

    std::string random_string;

    for (std::size_t i = 0; i < length; ++i)
    {
        random_string += characters[distribution(generator)];
    }

    return random_string;
}



std::vector<std::string> make_names(int number_of_names){
   std::vector<std::string> hold;
   for(int i =0; i<number_of_names; i++){
      hold.push_back(random_string(4));
   }
   return hold;
}



__global__ 
void solv(int n, std::vector <XY> *input, int *output)
{
  output[0] = 69;
}




int main()
{
   //  make test data NODE
   Node test_data;
   test_data.xy = data;

   test_data.name = make_names(10);
    
   //test
   std::cout<< (test_data.xy[0].x) <<"\n";std::cout<< (test_data.xy[0].y) <<"\n";std::cout<< (test_data.name[0]) << "\n";


   int N = (test_data.xy.size()  );

   std::cout<< "N: " <<N << "\n";//10

   // allocate memmory
   std::vector < XY > *de_input;
   cudaMalloc((void **) &de_input, N*sizeof(XY));

   int *de_counter;
   cudaMalloc((void **) &de_counter, N*sizeof(int));

   //stop
   cudaMemcpy( de_input, &test_data.xy, sizeof(test_data.xy), cudaMemcpyHostToDevice );


   //block, threads
   solv<<<1, 1>>>(N, de_input, de_counter);
   //block X threads = N


   // Wait for GPU to finish before accessing on host
   cudaDeviceSynchronize();


   int result[ N ];
   result[0] = 99;

   // Once the kernel has completed, we initiate a transfer of the result data *back to the CPU*.
   // Note that the `cudaMemcpyDeviceToHost` constant denotes transferring data *from the GPU*.
   cudaMemcpy( result, de_counter, sizeof(de_counter), cudaMemcpyDeviceToHost );




   std::cout<< "RESULTS: "<< (result[0])<< "\n";


   // Free memory
   cudaFree(de_input);
   cudaFree(de_counter);

   return 0; 
}