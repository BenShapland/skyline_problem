#include <iostream>
#include <vector>
#include <chrono>     // timing library
#include <numeric>    // std::accumulate()
#include <cuda_runtime.h>
#include <cuda.h>
#include <thrust/sort.h>



#include "data/data-sanity-check.hpp"
// #include "data/test-data.hpp"
// #include "data/data.cpp"

#define N 16 // num_blocks * num_thread_per_block 
#define num_blocks 1
#define num_thread_per_block  16 //2048


// #define N 600000 // num_blocks * num_thread_per_block 
// #define num_blocks 600
// #define num_thread_per_block  1000 //2048


// __constant__  XY de_data_array[N];
__device__  XY de_data_array[N]; // DATA XY values

__device__  int manhatten_array[N]; // Manhatten distance

__device__ int original_index[N]; // original index




//dom returns True if a dominates b else false
__host__ __device__
bool dom(XY a, XY b){
   bool a_better =false;
   a_better = ((a.x < b.x)&&(a.y <= b.y)) || ((a.x <= b.x)&&(a.y < b.y));
   return a_better;

}


__host__ __device__ bool operator<(XY a, XY b) { 
   if(a.x == b.x){
      if(a.y == b.y) return true;
   } 
   return false;

};

__host__ __device__
bool distance_sort(XY a, XY b){
   if(a.x == b.x){
      if(a.y == b.y) return true;
   } 
   return false;

}


__global__
void print_it_all(){

   for(int i =0 ; i < N ; i++){
      printf("%d %d\n",de_data_array[i].x,de_data_array[i].y);
   }
}





// __global__
// void wtf( XY *data){
//    for(int i =0 ; i < N ; i++){
//       printf("%d %d\n",de_data_array[i].x,de_data_array[i].y);
//    }

//    thrust::sort(data,data+N,distance_sort);

//    for(int i =0 ; i < N ; i++){
//       printf(gpu:
	nvcc -O3  solution_gpu.cu -o gpu 

   "%d %d\n",de_data_array[i].x,de_data_array[i].y);
//    }
// }




int main()


{
  
   // int seed = 1;
   // XY data_array[N];
   // xy_data_gen(data_array,N,seed);
   
   // char char_data[N*4];
   // char_array_gen(char_data,N,seed);

   cudaMemcpyToSymbol(de_data_array, &data_array, N*sizeof(XY));  //Save to global

   
   XY * test;
   cudaMalloc((void **) &test, N*sizeof(XY));
   cudaMemcpy(test,data_array,N*sizeof(XY),cudaMemcpyHostToDevice);

   wtf<<<1,1>>>(test);
   cudaDeviceSynchronize();

   // thrust::sort(test,test+N,distance_sort);




   // void* data_ptr = 0;
   // cudaGetSymbolAddress(&data_ptr, &data_array);
   // thrust::device_ptr<XY> data_first(reinterpret_cast<XY*>(&data_ptr));

  

   // thrust::sort(data_first,data_first+N,distance_sort);
   // cudaDeviceSynchronize();

   // print_it_all<<<1,1>>>();
   // cudaDeviceSynchronize();







   // char *de_char_names;
   // cudaMalloc((void **) &de_char_names, (4*N)*sizeof(char)); 

   // cudaMemcpy( de_char_names, char_data, (4*N)*sizeof(char), cudaMemcpyHostToDevice );
   
   
   // // START
   // auto const start_time = std::chrono::system_clock::now();

   // // Make manhatten distance array
   // MakeManhattan <<<num_blocks,num_thread_per_block >>>();
   // cudaDeviceSynchronize();

   // // Setup pointers to adresses in device for thrust sort
   // void* array_ptr = 0;
   // cudaGetSymbolAddress(&array_ptr, manhatten_array);
   // thrust::device_ptr<int> manhattan_first(reinterpret_cast<int*>(array_ptr));
   
   // // MAKE COPY OF MANHATEN for sorting again
   // thrust::device_vector<int> HOLD (manhattan_first,manhattan_first+N);
   // cudaDeviceSynchronize();

   // void* data_ptr = 0;
   // cudaGetSymbolAddress(&data_ptr, de_data_array);
   // thrust::device_ptr<XY> data_first(reinterpret_cast<XY*>(data_ptr));
   
   // // Sort DATA based on manhatten distance array
   // thrust::sort_by_key(manhattan_first, manhattan_first + N, data_first);
   // // Sort the original indexs based on HOLD (unsorted manhatten)
   // void* index_ptr = 0;
   // cudaGetSymbolAddress(&index_ptr, original_index);
   // thrust::device_ptr<int> index_first(reinterpret_cast<int*>(index_ptr));

   // thrust::sort_by_key(HOLD.begin(), HOLD.end(), index_first);
   // cudaDeviceSynchronize();


   // test <<< 1,1 >>>(de_char_names);
   // // print_it_all<<<1,1>>>();
   // cudaDeviceSynchronize();


   // // END
   // auto const end_time = std::chrono::system_clock::now();
   // auto const elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>( end_time - start_time );
   // std::cout << "time: " << ( elapsed_time.count() ) << " us" << std::endl;
   

   return 0; 
}



