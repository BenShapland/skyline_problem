#include <iostream>
#include <vector>
#include <chrono>     // timing library
#include <numeric>    // std::accumulate()


#include <iostream> // for outputting (printing) to streams (e.g., the terminal)
#include <random> 	// std::rand, std::srand, std::default_random_engine
#include <cmath>	// sqrt()
#include <cstring>   // std::strcmp()
#include <fstream>   // std::ofstream
#include <stdlib.h>  // srand(), rand()
#include <algorithm> // std::sort(), std::for_each()
#include <vector>
#include <sstream>

#include <cuda_runtime.h>
#include <cuda.h>
// #include "Node.h"
#include "data/data.cpp"

// #include "data/data-sanity-check.hpp"
// #include "data/test-data.hpp"


#define N 60000 // num_blocks * num_thread_per_block 
#define num_blocks 60
#define num_thread_per_block  1000 //2048


__device__  XY de_data_array[N];


//dom returns True if a dominates b else false
__host__ __device__
bool dom(XY a, XY b){
   bool a_better =false;
   a_better = ((a.x < b.x)&&(a.y <= b.y)) || ((a.x <= b.x)&&(a.y < b.y));
   return a_better;

}


__global__ 
void name_maker(const char *input, int *output){
   int index = threadIdx.x + (blockIdx.x* num_thread_per_block);

 
   if(output[index] != 80085){
      int R_INDEX = threadIdx.x*4 + (blockIdx.x* num_thread_per_block *4);
      printf("%c%c%c%c, "
      ,input[R_INDEX],input[R_INDEX+1],input[R_INDEX+2],input[R_INDEX+3]);
      printf("(%d,%d) \n", de_data_array[index].x,de_data_array[index].y);
   }

}

// test a single block                                                 
__global__ void one_stencil (int *counter, int n)
{
   
   // extern __shared__ XY s[];
   __shared__ XY s[num_thread_per_block];
   
   int localId = threadIdx.x;

   int globalId;

   int index = localId + num_thread_per_block*blockIdx.x;

   XY MY_NODE = de_data_array[index];

   // MIGHT WANT TO CLEAN UP I so that blocks dont just copy from the same location over and over again;

   for(int i =0; i< num_blocks; i++){
      // copy
      globalId = localId + num_thread_per_block*i;
      s[localId] = de_data_array[globalId];
      // sync - can it just be threads in a block
      __syncthreads();
      // solv
      for(int k=0;k<num_thread_per_block;k++){
         if( dom(s[k],MY_NODE) ){

            counter[index] = 80085;
            // return;
            for(int j =i; j<num_blocks;j++){
                  __syncthreads();
                  globalId = localId + num_thread_per_block*j;
                  s[localId] = de_data_array[globalId];
                  __syncthreads();
            }
            return;
         }
      }
      // sync
      __syncthreads();
   }

}

__global__ 
void solv( int * counter )
{
   int index = threadIdx.x + (blockIdx.x * num_thread_per_block);

   for(int i=0; i<N ; i++){

      if( dom(de_data_array[i],de_data_array[index] ) ){
         counter[index] = 80085;
         return;  // added this line
      }    
   }

}



int main(int argc, char** argv){
    
   int seed=1;   // default value
   if(argc ==2){
      std::istringstream a1(argv[1]);
      a1>>seed;
   }
  
   XY data_array[N];
   xy_data_gen(data_array,N,seed);
   
   char char_data[N*4];
   char_array_gen(char_data,N,seed);
   // Copy to Global
   cudaMemcpyToSymbol(de_data_array, &data_array, N*sizeof(XY));  
   
   // To store from solve
   int *de_counter;
   cudaMalloc((void **) &de_counter, N*sizeof(int));
   

   char *de_char_names;
   cudaMalloc((void **) &de_char_names, (4*N)*sizeof(char)); 

   cudaMemcpy( de_char_names, char_data, (4*N)*sizeof(char), cudaMemcpyHostToDevice );
   

   // START
   auto const start_time = std::chrono::system_clock::now();
   
   one_stencil<<<num_blocks, num_thread_per_block>>>(de_counter,N);
   // solv<<<num_blocks, num_thread_per_block>>>(de_counter);
   cudaDeviceSynchronize();

   // device to host
   // cudaMemcpy( result, de_counter, N*sizeof(int), cudaMemcpyDeviceToHost );
  
   name_maker<<<num_blocks, num_thread_per_block>>>(de_char_names, de_counter);
   cudaDeviceSynchronize();


   // END
   auto const end_time = std::chrono::system_clock::now();
   auto const elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>( end_time - start_time );
   std::cout << "time: " << ( elapsed_time.count() ) << " us" << std::endl;
   
   //free
   cudaFree(de_counter);
   cudaFree(de_char_names);

   return 0; 
}



