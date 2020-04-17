#include <iostream>
#include <vector>
#include <chrono>     // timing library
#include <numeric>    // std::accumulate()
#include <cuda_runtime.h>
#include <cuda.h>
#include "data/data.cpp"
// #include "data/data-sanity-check.hpp"
// #include "data/test-data.hpp"

#define N 5000
#define num_blocks 5
#define num_thread_per_block 1000

__constant__  XY de_data_array[N];

__host__ __device__
bool dom_old(XY a, XY b){
   if( ((a.x < b.x)&&(a.y <= b.y)) || ((a.x <= b.x)&&(a.y < b.y))){
      return true; 
   }
   return false;
}


//dom returns True if a dominates b else false
__host__ __device__
bool dom(XY a, XY b)
{
   bool a_better =false;
   a_better = ((a.x < b.x)&&(a.y <= b.y)) || ((a.x <= b.x)&&(a.y < b.y));
   return a_better;

}


__global__ 
void name_maker(const char *input, int *output)
{
   int index = threadIdx.x + (blockIdx.x* num_thread_per_block); 
   if(output[index] != 80085){
      int R_INDEX = threadIdx.x*4 + (blockIdx.x* num_thread_per_block *4);
      printf("%c%c%c%c\n"
      ,input[R_INDEX],input[R_INDEX+1],input[R_INDEX+2],input[R_INDEX+3]);
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


int main(int argc, char** argv)
{
   
   int seed=1;   // default value
   if(argc ==2){
      std::istringstream a1(argv[1]);
      a1>>seed;
   }
   XY data_array[N];
   xy_data_gen(data_array,N,seed);
   char char_data[N*4];
   char_array_gen(char_data,N,seed);

   
   cudaMemcpyToSymbol(de_data_array, &data_array, N*sizeof(XY));  //Save to constant


   int *de_counter;
   cudaMalloc((void **) &de_counter, N*sizeof(int));
   

   char *de_char_names;
   cudaMalloc((void **) &de_char_names, (4*N)*sizeof(char)); 


   int result[ N ];

   cudaMemcpy( de_counter, &result, sizeof(result), cudaMemcpyHostToDevice );
   
   //copy names
   cudaMemcpy( de_char_names, char_data, (4*N)*sizeof(char), cudaMemcpyHostToDevice );
   
   auto const start_time = std::chrono::system_clock::now();


   solv<<<num_blocks, num_thread_per_block>>>(de_counter);
   cudaDeviceSynchronize();

   
   name_maker<<<num_blocks, num_thread_per_block>>>(de_char_names, de_counter);
   cudaDeviceSynchronize();

   auto const end_time = std::chrono::system_clock::now();
   auto const elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>( end_time - start_time );
   std::cout << "time: " << ( elapsed_time.count() ) << " us" << std::endl;
   
   cudaMemcpy( result, de_counter, N*sizeof(int), cudaMemcpyDeviceToHost );

   //free
   cudaFree(de_counter);
   cudaFree(de_char_names);

   return 0; 
}



