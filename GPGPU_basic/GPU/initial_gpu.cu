
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

   int index = threadIdx.x + blockIdx.x ;
   for(int i=0; i<n ; i++){
      if( dom(input[index],input[i] ) ){
         output[i] = 80085; // test
         
      }    
   }
}
__global__ 
void name_maker(const char *input, int *output){
   int index = threadIdx.x + blockIdx.x;


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

   char *de_char_names;
   cudaMalloc((void **) &de_char_names, (4*N)*sizeof(char)); 


   XY *de_input;
   cudaMalloc((void **) &de_input, N*sizeof(XY));


   int *de_counter;
   cudaMalloc((void **) &de_counter, N*sizeof(int));

   auto const start_time = std::chrono::system_clock::now();


   cudaMemcpy( de_input, &data_array, sizeof(XY)*N, cudaMemcpyHostToDevice );
   
   
   int result[ N ];
   for(int i =0; i<N;i++){
      result[i]=0;
   }

   cudaMemcpy( de_counter, &result, sizeof(result), cudaMemcpyHostToDevice );

   cudaMemcpy( de_char_names, char_data, (4*N)*sizeof(char), cudaMemcpyHostToDevice );

;
   solv<<<1, N>>>(N, de_input, de_counter);
   //block X threads = N



   // Wait for GPU to finish before accessing on host
   cudaDeviceSynchronize();

   name_maker<<<1, N>>>(de_char_names, de_counter);


   cudaDeviceSynchronize();// probably dont need this


   // Once the kernel has completed, we initiate a transfer of the result data *back to the CPU*.
   // Note that the `cudaMemcpyDeviceToHost` constant denotes transferring data *from the GPU*.
   cudaMemcpy( result, de_counter, N*sizeof(int), cudaMemcpyDeviceToHost );


   auto const end_time = std::chrono::system_clock::now();
   auto const elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>( end_time - start_time );
   std::cout << "time: " << ( elapsed_time.count() ) << " us" << std::endl;
   

   cudaFree(de_input);
   cudaFree(de_counter);
   cudaFree(de_char_names);
   
   return 0; 
}



