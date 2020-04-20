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


__device__  XY de_data_array[N]; // DATA XY values
__device__  int manhatten_array[N]; // Manhatten distance
__device__ int original_index[N]; // original index


//dom returns True if a dominates b else false
__host__ __device__
bool dom(XY a, XY b)
{
   bool a_better =false;
   a_better = ((a.x < b.x)&&(a.y <= b.y)) || ((a.x <= b.x)&&(a.y < b.y));
   return a_better;
}


// spawn a thread for every node 
// cacluate the manhaten distance and store to an array 
__global__
void MakeManhattan()
{
   int index = threadIdx.x + (blockIdx.x * num_thread_per_block);
   int man = de_data_array[index].x + de_data_array[index].y;
   // printf("at index %d : %d\n",index,man);
   manhatten_array[index] = man;
   original_index[index] = index;
   // printf("FROM ARRAY at index %d : %d\n",index, manhatten_array[index]);
}

__global__
void compare_D_to_batch(int index_of_batch,int *de_index){
  // line 6-12 compare each node in D to the first batch size.
   //if a point is dominated it is added to a list of dominated points
   //and the thread returns

   int index = threadIdx.x + (blockIdx.x * num_thread_per_block);

   // printf("index[%d] threadID %d BlockID %d\n",index,threadIdx.x,blockIdx.x);
   //compare to global
   // if dom mark it 
   // if im dom return
   for(int i =index_of_batch; i < N; i++){
      // if im domed return
      if(de_data_array[index].x == 80085){
         return;
      }
      // if i dom some node set it to 80085
      if(dom(de_data_array[index],de_data_array[i])){
         de_data_array[i].x = 80085;
      }

   }
   if(de_data_array[index].x != 80085){
      // printf("original index: %d with (%d,%d)\n",original_index[index],de_data_array[index].x,de_data_array[index].y);
      de_index[index] = original_index[index];
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


   // Set-up 
   //--------------------------------------------------------------------------------------

   cudaMemcpyToSymbol(de_data_array, &data_array, N*sizeof(XY));  //Save to global
   
   // Make manhatten distance array
   MakeManhattan <<<num_blocks,num_thread_per_block >>>();
   cudaDeviceSynchronize();

   // Setup pointers to adresses in device for thrust sort
   void* array_ptr = 0;
   cudaGetSymbolAddress(&array_ptr, manhatten_array);
   thrust::device_ptr<int> manhattan_first(reinterpret_cast<int*>(array_ptr));
   
   // MAKE COPY OF MANHATEN for sorting again
   thrust::device_vector<int> HOLD (manhattan_first,manhattan_first+N);
   cudaDeviceSynchronize();

   void* data_ptr = 0;
   cudaGetSymbolAddress(&data_ptr, de_data_array);
   thrust::device_ptr<XY> data_first(reinterpret_cast<XY*>(data_ptr));
   
   // Sort DATA based on manhatten distance array
   thrust::sort_by_key(manhattan_first, manhattan_first + N, data_first);
   // Sort the original indexs based on HOLD (unsorted manhatten)
   void* index_ptr = 0;
   cudaGetSymbolAddress(&index_ptr, original_index);
   thrust::device_ptr<int> index_first(reinterpret_cast<int*>(index_ptr));

   thrust::sort_by_key(HOLD.begin(), HOLD.end(), index_first);
   cudaDeviceSynchronize();

   // cudaFree(index_first);
   // free thrust hold???

   //--------------------------------------------------------------------------------------


   /*
      line 6-12 compare each node in D to the first batch size.
      if a point is dominated it is added to a list of dominated points
      and the thread returns
   */

   // size of batch
   int size_of_batch = N;  // MIGHT WANT TO CHANGE THIS UP A BIT
   int result[ size_of_batch ];
   for(int i=0; i<size_of_batch;i++){
      result[i] = -1;
   }

   int *de_counter;
   cudaMalloc((void **) &de_counter, N*sizeof(int));


   // cudaMemcpy( de_index, &batch_index, sizeof(int)*size_of_batch, cudaMemcpyHostToDevice );

   cudaMemcpy( de_counter, &result, sizeof(result), cudaMemcpyHostToDevice );


   int starting_place =0;
   
   // START
   auto const start_time = std::chrono::system_clock::now();
   
   // for(){
   compare_D_to_batch <<< 2,8 >>>(starting_place,de_counter);
   cudaDeviceSynchronize();

   // THIS DOES NOT WORK@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@2
   // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
   // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
   // Could try and copy over soltion block by block

   cudaMemcpy( result, de_counter, N*sizeof(int), cudaMemcpyDeviceToHost ); 

   cudaDeviceSynchronize();

   for(int k = 0; k < size_of_batch; k++ ){
      if (result[k] != -1){
         int dex = result[k]*4;
         printf("%c%c%c%c\n", 
         char_data[dex],
         char_data[dex+1],
         char_data[dex+2],
         char_data[dex+3]
         );
      }
   }

   // END
   auto const end_time = std::chrono::system_clock::now();
   auto const elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>( end_time - start_time );
   std::cout << "time: " << ( elapsed_time.count() ) << " us" << std::endl;

   cudaFree(de_counter);


   // }
   //line 13 now that all threads have finished. Remove the dominated points from D


   //line 14-15 record the NON-dominated points and remove them from D.
   //(MIGHT BE ABLE TO RETURN THEM HERE ASWELL)

   //THIS IS ALL LOOPED THROUGH UNTILL THE DATA SET BECOMES 0\
   //each time we loop we will romove batch size number of points
   //except for the last run
   


      // FREE SHIT PLEASE


   return 0; 
}



