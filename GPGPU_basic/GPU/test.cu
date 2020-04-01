
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
 #include <chrono>     // timing library
#include <numeric>    // std::accumulate()
 
//  #include "Node.h"
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
 

 __host__ __device__
 bool dom(XY a, XY b){
    if( ((a.x < b.x)&&(a.y <= b.y)) || ((a.x <= b.x)&&(a.y < b.y))){
        return true; 
    }
    return false;
 }
 
 __global__ 
 void solv(int n, XY *input, int *output)
 {
 // Printing input
    int index = threadIdx.x;
   //  printf("Input %d, thread %d\n", input[index].x, threadIdx.x);  
    for(int i=0; i<n ; i++){
       // if add input[index] doms input[i]
       if( dom(input[index],input[i] ) ){
          output[i] = 80085; // test
          
         //  printf("Input %d, thread %d\n", input[index].x, threadIdx.x);  
       }    
    }
 }
 
 
 int main()
 {



   int N = sizeof(data_array)/ sizeof(XY);

   // std::cout<<"size N: "<<N<<"\n";
 
    XY *de_input;
    cudaMalloc((void **) &de_input, N*sizeof(XY));


    int *de_counter;
    cudaMalloc((void **) &de_counter, N*sizeof(int));

   auto const start_time = std::chrono::system_clock::now();


    cudaMemcpy( de_input, &data_array, sizeof(XY)*N, cudaMemcpyHostToDevice );
    
    // std::cout<<"size of(xy)" << sizeof(de_input);
    
    int result[ N ];
   //  for (int i =0;i<N;i++){
   //     result[i] = 0;
   //  }
    cudaMemcpy( de_counter, &result, sizeof(result), cudaMemcpyHostToDevice );
 
 
    //block, threads
    solv<<<1, N>>>(N, de_input, de_counter);
    //block X threads = N
 
 
    // Wait for GPU to finish before accessing on host
    cudaDeviceSynchronize();
 
 
    // int result[ N ];
    // for (int i =0;i<N;i++){
    //    result[i] = 999;
    // }
 
    // Once the kernel has completed, we initiate a transfer of the result data *back to the CPU*.
    // Note that the `cudaMemcpyDeviceToHost` constant denotes transferring data *from the GPU*.
    cudaMemcpy( result, de_counter, N*sizeof(int), cudaMemcpyDeviceToHost );
 

    // Generate Final Result
   Node final_result;
   for (int i =0;i<N;i++){
      // std::cout<< i<<" " <<(result[i])<< "\n";
      if (result[i] == 0){
         // final_result.add(XY_array.x,XY_array.y,name[i]);
         std::cout<<"x: " << data_array[i].x <<" y: "<<data_array[i].y<<"\n";
      }

   }
      
    //goal 0 , 1, 4, 7, 14
      
 
    // Free memory
    cudaFree(de_input);
    cudaFree(de_counter);

    auto const end_time = std::chrono::system_clock::now();
    auto const elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>( end_time - start_time );
    std::cout << "time: " << ( elapsed_time.count() ) << " us" << std::endl;
    return 0; 
 }