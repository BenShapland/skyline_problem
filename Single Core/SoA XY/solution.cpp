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
    std::cout<< ret;

    return " ";


} // End func solve




int instance( int size, int seed){

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
    // std::cout << "time CPU: " << ( elapsed_time.count() ) << " us" << std::endl;

    return elapsed_time.count();
}

int main(int argc, char** argv)
{
   int size = 5000;
   int seed = 1;
   int number_of_runs = 1000;
   
   int total_time= 0;

   if(argc < 2 ){
        std::cout<<"Mode: compare or bench\n";

      
      return 0;
   } 
    // define input,size,seeds
    
    std::string input = argv[1];
    
    if(argc >=3){    // size input
        std::istringstream a2(argv[2]);
        a2>>size;
    }

    if(argc == 4){    // seed -> comapring or number_of_runs -> benchmarking
        std::istringstream   a3(argv[3]);
        a3>>seed;
        number_of_runs = seed;
    }
    // std::cout<<"-------------mode: "<<input<<"--------\n";

    if (input == "bench" ){
        printf("----------BENCHMARKING-----------\n");
        std::cout<<"num of data_points: "<<size<<"\n";
        std::cout<<"num of test runs: "<<number_of_runs<<"\n";
        // BENCHMARKING

        for(auto i=0; i <number_of_runs; i++){
            std::srand( (i *i*10000)/7 +4 );
            seed = std::rand(); 
            total_time += instance(size,seed);
            std::cout<<"\n";
        }
        int avg_time = total_time/number_of_runs;
        std::cout<<"avg_time: "<< avg_time <<" \n";
    
    }else if(input == "compare"){
        printf("----------COMPARISON-----------\n");  
        std::cout<<"num of data_points: "<<size<<"\n";  
        std::cout<<"using seed: "<<seed<<"\n";
    
        total_time += instance(size,seed);
        std::cout<<"\n";
    }else{
        std::cout<<"Mode: compare or bench\n";

      }
   return 0;

}

