
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

#include "test-data.hpp"
// #include "data-sanity-check.hpp"




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
   // int index = threadIdx.x + blockIdx.x*(1024) ;
   int index = threadIdx.x + blockIdx.x ;
   //  printf("Input %d, thread %d\n", input[index].x, threadIdx.x);  
   for(int i=0; i<n ; i++){
      // if add input[index] doms input[i]
      if( dom(input[index],input[i] ) ){
         output[i] = 80085; // test
         
         //  printf("Input %d, thread %d\n", input[index].x, threadIdx.x);  
      }    
   }
}
__global__ 
void name_maker(const char *input, int *output){
   // int index = threadIdx.x + blockIdx.x*(1024);
   int index = threadIdx.x + blockIdx.x;

   // printf("In GPU section\n");
   
   // if(output[threadIdx.x + blockIdx.x*(1024)] == 0){
   if(output[index] == 0){
      int R_INDEX = threadIdx.x*4 + blockIdx.x;
      // printf("out==0\n");
      printf("name %c%c%c%c INDEX %d BLOCK ID %d\n"
      ,input[R_INDEX],input[R_INDEX+1],input[R_INDEX+2],input[R_INDEX+3], index, blockIdx.x);
   }

}


int main()
{
   int N = sizeof(data_array)/ sizeof(XY);
   // std::cout<<"size N: "<<N<<"\n"; 

   char *de_char_names;
   cudaMalloc((void **) &de_char_names, (4*N)*sizeof(char)); //5 becasue of ending \0


   XY *de_input;
   cudaMalloc((void **) &de_input, N*sizeof(XY));


   int *de_counter;
   cudaMalloc((void **) &de_counter, N*sizeof(int));

   auto const start_time = std::chrono::system_clock::now();


   cudaMemcpy( de_input, &data_array, sizeof(XY)*N, cudaMemcpyHostToDevice );
   
   // std::cout<<"size of(xy)" << sizeof(de_input);
   
   int result[ N ];
   for(int i =0; i<N;i++){
      result[i]=0;
   }

   cudaMemcpy( de_counter, &result, sizeof(result), cudaMemcpyHostToDevice );

   cudaMemcpy( de_char_names, char_data, (4*N)*sizeof(char), cudaMemcpyHostToDevice );

   //block, threads
   //TEST
   // 1024
   // solv<<<N, 1>>>(N, de_input, de_counter);
   solv<<<N, 1>>>(N, de_input, de_counter);
   //block X threads = N



   // Wait for GPU to finish before accessing on host
   cudaDeviceSynchronize();

   //TEST
   name_maker<<<N, 1>>>(de_char_names, de_counter);


   cudaDeviceSynchronize();// probably dont need this


   // Once the kernel has completed, we initiate a transfer of the result data *back to the CPU*.
   // Note that the `cudaMemcpyDeviceToHost` constant denotes transferring data *from the GPU*.
   cudaMemcpy( result, de_counter, N*sizeof(int), cudaMemcpyDeviceToHost );


   auto const end_time = std::chrono::system_clock::now();
   auto const elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>( end_time - start_time );
   std::cout << "time: " << ( elapsed_time.count() ) << " us" << std::endl;
   
   //  Generate Final Result
   std::cout<<"____________________________________________________-";

   // Free memory
   cudaFree(de_input);
   cudaFree(de_counter);

   //TEST
   cudaFree(de_char_names);
   
   return 0; 
}



