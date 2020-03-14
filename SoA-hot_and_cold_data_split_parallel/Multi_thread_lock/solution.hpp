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



bool Dominate(int ax,int ay, int bx, int by ){
    if( ((ax < bx)&&(ay <= by)) || ((ax <= bx)&&(ay < by))){

        return true;

    }
    return false;
}

//BROKEN
// std::string  solve_old (Node const& input )  
// {

//     assert(input.xy.size() == input.name.size());
    
    
//    	Node best;  // vector of nodes
//     bool update = true;


//     int count =0;



//     for (auto i =0u ; i <  input.xy.size(); i++)
//     { 
//         count = 0;
//         for(auto k = 0u; k<best.xy.size(); k++){
    
//             if(Dominate(best.xy[k].x,best.xy[k].y ,input.xy[i].x,input.xy[i].y ) || (equal(best.xy[k].x,best.xy[k].y, input.xy[i].x, input.xy[i].y)) ){
//                 count --;
//                 break;
//             }

//         }

//         if(count == 0){
//             best.add(input.xy[i].x,input.xy[i].y,input.name[i] );  

            
//             for(auto j = 0u; j<best.xy.size(); j++){
//                 if(Dominate(input.xy[i].x,input.xy[i].y,best.xy[j].x,best.xy[j].y)){
//                     best.xy.erase(best.xy.begin()+ j); // x
//                     best.name.erase(best.name.begin()+ j); // name

//                 }
//             }

//         } //  Input Dom all of best
//     }

//     std::string ret;   // save return value
//     std::cout<<"\n";
//     for(auto i=0u;i<best.name.size();i++){
    
//         // ret = ret + best.name[i] +" ";
//         std::cout<<best.name[i] + " "  <<best.xy[i].x <<" " << best.xy[i].y << "\n";

//     }
//     ret =ret+"\n";

//     // return "test\n";


// } 

/// ------------------Parallel Start-------------------------------/
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


    // parallel
    // #pragma omp parallel for num_threads( num_cores )
    for (auto i =0u ; i <  input.xy.size(); i++) 
        // #pragma omp critical 
        // {
    {

        // // auto const th_id = omp_get_thread_num(); 
        bool written = false;  
        bool dom =false;

        for(auto k = 0u; k<best.xy.size(); k++){  // compare input and best


            // if index best locked -> wait 
            // else we continue
           
            if(Dominate(input.xy[i].x,input.xy[i].y,  best.xy[k].x,best.xy[k].y  ) ){  // Input Dominate Best ->  Good input -> Save it
        //   
// 
                // #pragma omp critical 
                // {
                // if(Dominate(input.xy[i].x,input.xy[i].y,  best.xy[k].x,best.xy[k].y  ) ){
                // write input[i] to best[k]
    
                best.xy[k].x = input.xy[i].x;
                best.xy[k].y = input.xy[i].y;
                best.name[k] = input.name[i];
                written = true;
            
                // }
                // }

            }

         
            // else if(Dominate(best.xy[k].x,best.xy[k].y,input.xy[i].x,input.xy[i].y ))  // Best dominate Input -> Input not needed
            else if(Dominate(best.xy[k].x,best.xy[k].y ,input.xy[i].x,input.xy[i].y ) || (equal(best.xy[k].x,best.xy[k].y, input.xy[i].x, input.xy[i].y)) )
            {
                dom = true;
                break;
            }

        } // loop best

        if( !dom   && !written){

            XY xy_node( input.xy[i].x,input.xy[i].y);
            // #pragma omp critical
            // {
            best.xy.push_back(xy_node) ;
            best.name.push_back(input.name[i]); 
        }

    }

        // }


    // } // for input

    
    assert(best.xy.size() == best.name.size());


    // return solve(best);

    // std::string ret;   // save return value
    // std::cout<<"\n";
    // for(auto i=0u;i<best.name.size();i++){
    
    //     // ret = ret + best.name[i] +" ";
    //     std::cout<<best.name[i] + " "  <<best.xy[i].x <<" " << best.xy[i].y << "\n";

    // }
    // ret =ret+"\n";
    // return ret;

    std::string ret;
    bool GOT_IT = false;
    vector<std::string>done;   // save return value
    for(auto i=0u;i<best.name.size();i++){
        GOT_IT = false;
        for(auto j=0u;j<done.size();j++){
        //if not in Done add and breake
            if(done[j] == best.name[i]){
                GOT_IT = true;
                break;
            }
        }
        if(!GOT_IT){
            done.push_back(best.name[i]);
            ret = ret + best.name[i] +" ";
        }
    }
    ret =ret+"\n";




    
    return ret;

    // return "test\n";



} // End func


/// ----------------Parallel End---------------------------------/


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

        // // auto const th_id = omp_get_thread_num(); 
        bool written = false;  
        bool dom =false;

        for(auto k = 0u; k<best.xy.size(); k++){  // compare input and best


            // if index best locked -> wait 
            // else we continue
           
            if(Dominate(input.xy[i].x,input.xy[i].y,  best.xy[k].x,best.xy[k].y  ) ){  // Input Dominate Best ->  Good input -> Save it
        //   
// 
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

         
            // else if(Dominate(best.xy[k].x,best.xy[k].y,input.xy[i].x,input.xy[i].y ))  // Best dominate Input -> Input not needed
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

        // }


    // } // for input

    
    assert(best.xy.size() == best.name.size());


    // return solve(best);

    std::string ret;   // save return value
    std::cout<<"\n";
    for(auto i=0u;i<best.name.size();i++){
    
        ret = ret + best.name[i] +" ";
        // std::cout<<best.name[i] + " "  <<best.xy[i].x <<" " << best.xy[i].y << "\n";

    }
    ret =ret+"\n";
    return ret;

    // return "test\n";



} // End func


void merge(Node n1,Node n2){

    std::cout<<"Printing n1";
    n1.print_node();
    std::cout<<"Printing n2";
    n2.print_node();


    n1.xy.insert(n1.xy.end(), n2.xy.begin(), n2.xy.end());
    n1.name.insert(n1.name.end(), n2.name.begin(), n2.name.end());

    std::cout<<"Printing n1 after append";
    n1.print_node();



} // 






} 
}
#endif 



