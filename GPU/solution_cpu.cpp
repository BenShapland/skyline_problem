#include <cassert>		 // assert()
#include <unordered_map>
#include <iostream> 
#include <omp.h>    // for multi-core parallelism
#include <chrono> 
#include <vector>
// #include "data/test-data.hpp"
#include "data/data.cpp"
using std::vector;


bool Dominate(int ax,int ay, int bx, int by )
{
    if( ((ax < bx)&&(ay <= by)) || ((ax <= bx)&&(ay < by))){

        return true;

    }
    return false;
}


std::string  solve (Node const& input )  
{
    
    int size_best = 100000;
    std::vector<XY> values;
    values.reserve(size_best);
    std::vector<std::string> n;
    n.reserve(size_best);
    n.size(); 

    Node best;
    best.xy = values;
    best.name = n;


    for (auto i =0u ; i <  input.xy.size(); i++) 
    {

        bool written = false;  
        bool dom =false;

        for(auto k = 0u; k<best.xy.size(); k++){  // compare input and best


            // if index best locked -> wait 
            // else we continue
            if(Dominate(input.xy[i].x,input.xy[i].y,  best.xy[k].x,best.xy[k].y  ) ){  // Input Dominate Best ->  Good input -> Save it
           
    
                best.xy[k].x = input.xy[i].x;
                best.xy[k].y = input.xy[i].y;
                best.name[k] = input.name[i];
                written = true;
            }
         
            else if(Dominate(best.xy[k].x,best.xy[k].y ,input.xy[i].x,input.xy[i].y ) || (equal(best.xy[k].x,best.xy[k].y, input.xy[i].x, input.xy[i].y)) )
            {
                dom = true;
                break;
            }

        } // loop best

        if( !dom   && !written){

            XY xy_node( input.xy[i].x,input.xy[i].y);
            best.xy.push_back(xy_node) ;
            best.name.push_back(input.name[i]); 
            // std::cout<<"INDEX: "<<i<<input.name[i]<<"\n";
        }

    }

    assert(best.xy.size() == best.name.size());

    std::string ret;
    bool GOT_IT = false;
    vector<std::string>done;   // save return value
    for(auto i=0u;i<best.name.size();i++){
        GOT_IT = false;
        for(auto j=0u;j<done.size();j++){
            if(done[j] == best.name[i]){
                GOT_IT = true;
                break;
            }
        }
        if(!GOT_IT){
            done.push_back(best.name[i]);
            ret = (ret + best.name[i] +" ") ;

        }
    }
    ret =ret+"\n";

    return ret;


} // End func


std::string  solve_parallel (Node const& input, int num_cores)  
{
    int size_best = 100000;
    std::vector<XY> values;
    values.reserve(size_best);
    std::vector<std::string> n;
    n.reserve(size_best);
    n.size(); 

    Node best;
    best.xy = values;
    best.name = n;

    // parallel
    #pragma omp parallel for num_threads( num_cores )
    for (auto i =0u ; i <  input.xy.size(); i++) 
    {
        bool written = false;  
        bool dom =false;

        for(auto k = 0u; k<best.xy.size(); k++){  // compare input and best

            // if index best locked -> wait 
            // else we continue
           
            if(Dominate(input.xy[i].x,input.xy[i].y,  best.xy[k].x,best.xy[k].y  ) ){  // Input Dominate Best ->  Good input -> Save it

                #pragma omp critical 
                {
                    if(Dominate(input.xy[i].x,input.xy[i].y,  best.xy[k].x,best.xy[k].y  ) ){
                    // write input[i] to best[k]
        
                    best.xy[k].x = input.xy[i].x;
                    best.xy[k].y = input.xy[i].y;
                    best.name[k] = input.name[i];
                    written = true;
                    }
                }

            }
            else if(Dominate(best.xy[k].x,best.xy[k].y ,input.xy[i].x,input.xy[i].y ) || (equal(best.xy[k].x,best.xy[k].y, input.xy[i].x, input.xy[i].y)) )
            {
                dom = true;
                break;
            }

        } // loop best

        if( !dom   && !written){

            XY xy_node( input.xy[i].x,input.xy[i].y);
            #pragma omp critical
            {
            best.xy.push_back(xy_node) ;
            best.name.push_back(input.name[i]); 
            }
        }

    }

    assert(best.xy.size() == best.name.size());

    std::string ret;
    bool GOT_IT = false;
    vector<std::string>done;   // save return value
    for(auto i=0u;i<best.name.size();i++){
        GOT_IT = false;
        for(auto j=0u;j<done.size();j++){
            if(done[j] == best.name[i]){
                GOT_IT = true;
                break;
            }
        }
        if(!GOT_IT){
            done.push_back(best.name[i]);
            ret = (ret + best.name[i] +" ") ;

        }
    }
    ret =ret+"\n";

    return ret;


} // End func



int main(int argc, char** argv){
    // MUST INCLUDE \// #include "test-data.hpp"
    // Node the_data;
    // the_data.xy = data;
    // the_data.name = data_name;

    int size=5000; // default
    int num_cores =6;
    int seed=1; // default


    if(argc >=2){ 
        std::istringstream a1(argv[1]);
        a1>>size;
    }
    if(argc >=3){ 
        std::istringstream a2(argv[2]);
        a2>>num_cores;
    }
    if(argc ==4){ 
        std::istringstream a3(argv[3]);
        a3>>seed;
    }

    std::cout<<"-------------num of data_points: "<<size<<"--------\n";
    std::cout<<"-------------number of cores: "<<num_cores<<"--------\n";
    std::cout<<"-------------Using seed: "<<seed<<"--------------\n";

    Node the_data;
    the_data.xy = xy_data_gen_vector(size,seed);

    char char_array[size*4];
    char_array_gen(char_array,size,seed);
    the_data.name = char_to_string_vector(char_array,size);;
    

   // start timer 
    auto const start_time = std::chrono::system_clock::now();
    std::string ans = solve(the_data);
    std::cout<<ans;

    // End timer 
    auto const end_time = std::chrono::system_clock::now();
    auto const elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>( end_time - start_time );
    std::cout << "time CPU: " << ( elapsed_time.count() ) << " us" << std::endl;


   // start timer 
   auto const start_time_parallel = std::chrono::system_clock::now();


    std::string ans_parallel = solve_parallel(the_data,num_cores);
    std::cout<<ans_parallel;

    // End timer 
    auto const end_time_parallel = std::chrono::system_clock::now();
    auto const elapsed_time_parallel = std::chrono::duration_cast<std::chrono::microseconds>( end_time_parallel - start_time_parallel );
    std::cout << "time CPU Parallel: " << ( elapsed_time_parallel.count() ) << " us" << std::endl;

    return 0;
}


