#include <iostream> // for outputting (printing) to streams (e.g., the terminal)
#include <random> 	// std::rand, std::srand, std::default_random_engine
#include <cmath>	// sqrt()
#include <cstring>   // std::strcmp()
#include <fstream>   // std::ofstream
#include <stdlib.h>  // srand(), rand()
#include <algorithm> // std::sort(), std::for_each()
#include <vector>
#include <sstream>

#include "Node.h"


void char_array_gen(char * char_array,int number_of_names, int seed){
    
    std::srand (seed);
    int n = number_of_names * 4;
    int rando = 0;
    
 
    std::string alphabet="abcdefghijklmnopqrstuvwxyz";
    for( auto i = 0u; i < n; ++i )
    {
        rando = std::rand() %26 ;
        char_array[i] = alphabet[rando]; 
          
    }

}


std::vector<  std::string > char_to_string_vector(char * char_array,int number_of_names){
    std::vector<  std::string > THE_NAMES;
    std::string A_NAME="abcd";
    int index = 0;
    for(int i =0;i<number_of_names;i++){
        
        for(int k =0; k <4 ; k++){
            A_NAME[k] = char_array[index];
            index++;
        }
        // add to vector
        THE_NAMES.push_back(A_NAME);
    }
    return THE_NAMES;
} 


void xy_data_gen(XY * data_array, int n, int seed){
   std::srand (seed);
   for( auto i = 0u; i < n; ++i )
    {
        auto const x = ( std::rand() %1000 & ~1u );
        auto const y = ( std::rand() %1000 & ~1u );
        data_array[i] = XY(x,y);
    }

}
std::vector< XY > xy_data_gen_vector(int n, int seed){
    std::srand (seed);
    std::vector<XY> data;
    for( auto i = 0; i < n; ++i )
        {
            auto const x = ( std::rand() %1000 & ~1u );
            auto const y = ( std::rand() %1000 & ~1u );
            data.push_back( XY(x,y));
            
        }
    return data;
}




// int main(){
//     int size =16;

// Testing Char array
    // char char_array[size*4];
    // char_array_gen(char_array,size,1);
    // for(int i =0; i< size*4; i++){
    //     std::cout<<char_array[i];
    // }
    // printf("\n");


// // Test Char Vector
//     // std::vector<  std::string >  char_vec = char_to_string_vector(char_array,size);
    
//     // for(int i=0;i<size;i++){
//     //     std::cout<<char_vec[i];
//     // }
//     // printf("\n");

// // Testing data_array
//     XY data[size];
//     xy_data_gen(data,size,1);
//     for(int i =0; i< size; i++){
//         std::cout<<data[i].x;
//     }
//     printf("\n");


// // Testing vector data 

//     std::vector<XY> data_array = xy_data_gen_vector(size,1);

//     for(int i=0;i<size;i++){
//         std::cout<<data_array[i].x;
//     }
//     printf("\n");


//     return 0;
// }