
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
   printf("Input %d, thread %d\n", input[index].x, threadIdx.x); 




   // int index = threadIdx.x;
   // for(int i=0; i<n ; i++){
   //    // if add input[index] doms input[i]
   //    if( dom(input[index],input[i] ) ){
   //       output[i] = 80085; // test
         
   //       printf("Input %d, thread %d\n", input[index].x, threadIdx.x);  
   //    }
      
   
   // }
   
}


int main()
{
   //  make test data NODE
   Node test_data;
   test_data.xy = data;
   XY * data_pointer = data;
   test_data.name = make_names(10);
    
   int test_array[10] = {0,1,2,3,4,5,6,7,8,9};


   //test
   std::cout<< (test_data.xy[0].x) <<"\n";std::cout<< (test_data.xy[0].y) <<"\n";std::cout<< (test_data.name[0]) << "\n";


   int N = (test_data.xy.size()  );

   std::cout<< "N: " <<N << "\n";//10

   // allocate memmory
   // std::vector < XY > *de_input;
   XY *de_input;


   cudaMalloc((void **) &de_input, N*sizeof(XY));

   int *de_counter;
   cudaMalloc((void **) &de_counter, N*sizeof(int));


   cudaMalloc((void **) &de_input, N*sizeof(XY));




   //stop
   cudaMemcpy( de_input, &data_pointer, sizeof(XY)*N, cudaMemcpyHostToDevice );
   
   // std::cout<<"size of(xy)" << sizeof(de_input);
   
   int result[ N ];
   for (int i =0;i<N;i++){
      result[i] = 999;
   }
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


   for (int i =0;i<N;i++){
      std::cout<< i<<" " <<(result[i])<< "\n";
   }
   
   //goal 0 , 1, 4, 7, 14


   // std::cout<< "0: "<< (result[0])<< "\n";
   // std::cout<< "1: "<< (result[1])<< "\n";
   // std::cout<< "2: "<< (result[2])<< "\n";
   // std::cout<< "3: "<< (result[3])<< "\n";
   // std::cout<< "4: "<< (result[4])<< "\n";

   // Free memory
   cudaFree(de_input);
   cudaFree(de_counter);

   return 0; 
}