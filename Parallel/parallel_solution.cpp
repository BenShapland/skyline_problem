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

std::string  solve_parallel (Node const& input, int num_cores)  
{
    int size_best = 1000;
    std::vector<XY> values;
    values.reserve(size_best);
    std::vector<std::string> n;
    n.reserve(size_best);
    n.size(); 

    Node best;
    best.xy = values;
    best.name = n;

    // printf("Starting Paralle Section\n");
    // parallel
    #pragma omp parallel for num_threads( num_cores )
    for (auto i =0u ; i <  input.xy.size(); i++) 
    {
        // int id = thread.id();
        // printf("outer for input\n");
        bool written = false;  
        bool dom =false;

        for(auto k = 0u; k<best.xy.size(); k++){  // compare input and best
            // printf("inner for \n");
            // if index best locked -> wait 
            // else we continue
           
            if(Dominate(input.xy[i].x,input.xy[i].y,  best.xy[k].x,best.xy[k].y  ) ){  // Input Dominate Best ->  Good input -> Save it

                #pragma omp critical 
                {

                    if(Dominate(input.xy[i].x,input.xy[i].y,  best.xy[k].x,best.xy[k].y  ) ){
                    // write input[i] to best[k]
                    // printf("if Dom \n");
                    best.xy[k].x = input.xy[i].x;
                    best.xy[k].y = input.xy[i].y;
                    best.name[k] = input.name[i];
                    written = true;
                    }
                }

            }
        
            // else if(Dominate(best.xy[k].x,best.xy[k].y ,input.xy[i].x,input.xy[i].y ) || (equal(best.xy[k].x,best.xy[k].y, input.xy[i].x, input.xy[i].y)) )
            else if(Dominate(best.xy[k].x,best.xy[k].y ,input.xy[i].x,input.xy[i].y )  )

            {
                // printf("elseif Dom \n");
                dom = true;
                break;
            }

        } // loop best

        if( !dom   && !written){
            // printf("if Dom \n");
            XY xy_node( input.xy[i].x,input.xy[i].y);
            #pragma omp critical
            {
            // printf("critical #2 \n");
            best.xy.push_back(xy_node) ;
            best.name.push_back(input.name[i]); 
            
            // std::cout << best.xy.size();
            }
        }

    }
    // printf("DONE");
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
    std::cout<<ret;

    return " ";


} // End func solve_parallel



int instance( int size, int num_cores, int seed){
    // MUST INCLUDE \// #include "test-data.hpp"
    // Node the_data;
    // the_data.xy = data;
    // the_data.name = data_name;

    Node the_data;
    the_data.xy = xy_data_gen_vector(size,seed);

    char char_array[size*4];
    char_array_gen(char_array,size,seed);
    the_data.name = char_to_string_vector(char_array,size);;
    
   // start timer 
   auto const start_time_parallel = std::chrono::system_clock::now();

    std::string ans_parallel = solve_parallel(the_data,num_cores);
    std::cout<<ans_parallel;

    // End timer 
    auto const end_time_parallel = std::chrono::system_clock::now();
    auto const elapsed_time_parallel = std::chrono::duration_cast<std::chrono::microseconds>( end_time_parallel - start_time_parallel );
    // std::cout << "time CPU Parallel: " << ( elapsed_time_parallel.count() ) << " us" << std::endl;

    return elapsed_time_parallel.count();
}

int main(int argc, char** argv)
{
   int size = 5000;
   int num_cores = 6;
   int seed = 1;
   int total_time= 0;

   if(argc < 2 ){
        std::cout<<"Mode: compare or bench\n";
      return 0;
   } 
    // define input,size,num_cores,seeds
    
    std::string input = argv[1];

    if(argc >=3){    // size input
        std::istringstream a2(argv[2]);
        a2>>size;
    }
    if(argc >=4){   // num_cores
        std::istringstream a3(argv[3]);
        a3>>num_cores;
    }
    if(argc == 5){    // seed -> comapring or number_of_runs -> benchmarking
        std::istringstream   a4(argv[4]);
        a4>>seed;
    }

    if (input == "bench" ){
        // BENCHMARKING
            std::srand( (seed *seed*10000)/7 +4 );
            seed = std::rand();
            // std::cout<<"index: "<< seed<<" SEED: "<< seed;
 
            total_time += instance(size,num_cores,seed);
            std::cout<<"\n";

        std::cout<<"time: "<< total_time <<" \n";
    
    }else if(input == "compare"){
        printf("----------COMPARISON-----------\n");
        std::cout<<"-------------Using data_points: "<<size<<"--------------\n";
        std::cout<<"-------------Using cores: "<<num_cores<<"--------------\n";
        std::cout<<"-------------Using seed: "<<seed<<"--------------\n";
        total_time += instance(size,num_cores,seed);
        std::cout<<"\n";
    }else{
        std::cout<<"Mode: compare or bench\n";
      }
   return 0;

}

