#include <cassert>		 // assert()
#include <unordered_map>
#include <iostream> 
#include <omp.h>    // for multi-core parallelism
#include <chrono> 
#include <vector>

#include "data/perf_data.hpp"
// #include "data/data.cpp"
// using std::vector;


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
    std::vector<std::string>done;   // save return value
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


int main(int argc, char** argv)
{
    int num_cores=4;
    Node the_data;
    the_data.xy = data;
    the_data.name = data_name;
    solve_parallel(the_data,num_cores);
   return 0;

}

