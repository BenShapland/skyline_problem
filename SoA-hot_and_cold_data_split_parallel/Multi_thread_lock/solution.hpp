#ifndef CS586_UNIQUE
#define CS586_UNIQUE

#include <cassert>		 // assert()
#include <unordered_map>
#include <iostream> 
#include <omp.h>    // for multi-core parallelism

// #include "point-data.hpp"


namespace skyline {
namespace solution {
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
  
    int num_cores =6;

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


std::string  solve_parallel (Node const& input )  
{
    
    int size_best = 100000;
    std::vector<XY> values;
    values.reserve(size_best);
  
    int num_cores =6;

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




} 
}
#endif 



