#ifndef CS586_UNIQUE
#define CS586_UNIQUE

#include <cassert>		 // assert()
#include <unordered_map>
#include <iostream> 
#include <omp.h>    // for multi-core parallelism



namespace skyline {
namespace solution {
using std::vector;



bool Dominate(int ax,int ay, int bx, int by ){
    if( ((ax < bx)&&(ay <= by)) || ((ax <= bx)&&(ay < by))){

        return true;

    }
    return false;
}


std::string  solve (Node const& input )  
{

    assert(input.xy.size() == input.name.size());
    
    
   	Node best;  // vector of nodes
    bool update = true;

    // int count_best = 0;
    int count =0;


    // while(update){
        for (auto i =0u ; i <  input.xy.size(); i++)
        { 
            // update = false;
            count = 0;
            for(auto k = 0u; k<best.xy.size(); k++){
       
                if(Dominate(best.xy[k].x,best.xy[k].y ,input.xy[i].x,input.xy[i].y ) || (equal(best.xy[k].x,best.xy[k].y, input.xy[i].x, input.xy[i].y)) ){
                    count --;
                    break;
                }

            }

            if(count == 0){
                best.add(input.xy[i].x,input.xy[i].y,input.name[i] );  // Best Updated fukkkk
                // count_best +=1;
                // update = true;
              
                for(auto j = 0u; j<best.xy.size(); j++){
                    if(Dominate(input.xy[i].x,input.xy[i].y,best.xy[j].x,best.xy[j].y)){
                        best.xy.erase(best.xy.begin()+ j); // x
                        // best[th_id].y.erase(best[th_id].y.begin()+ j); // y
                        best.name.erase(best.name.begin()+ j); // name

                    }
                }
            }
        }
   
    // }
    // std::cout<<"count_best:  "<<count_best<< "\n";
    std::string ret;   // save return value


    for(auto i=0u;i<best.name.size();i++){
    
        ret = ret + best.name[i] +" ";

    }
    ret =ret+"\n";

    return ret;


} 

/// ------------------Parallel Start-------------------------------/
std::string  solve_parallel (Node const& input )  
{

    assert(input.xy.size() == input.name.size());
   	
    std::vector<Node>  best;  // vector of nodes

 
    int count =0;
    int num_cores =1;  // Ensure num_cores are even

// one best node for each thread?
    for(int i=0;i<num_cores;i++){
        Node best_thread;
        best.push_back(best_thread);
    }


    // int th_id =0; // test
    #pragma omp parallel for num_threads( num_cores )
    for (auto i =0u ; i <  input.xy.size(); i++)

    { 
        
        count = 0;
        auto const th_id = omp_get_thread_num(); 

        for(auto k = 0u; k<best[th_id].xy.size(); k++){
    
            if(Dominate(best[th_id].xy[k].x,best[th_id].xy[k].y ,input.xy[i].x,input.xy[i].y ) || (equal(best[th_id].xy[k].x,best[th_id].xy[k].y, input.xy[i].x, input.xy[i].y)) ){
                count --;
                break;
            }

        }

        if(count == 0){
            best[th_id].add(input.xy[i].x,input.xy[i].y,input.name[i] );  

            
            for(auto j = 0u; j<best[th_id].xy.size(); j++){
                if(Dominate(input.xy[i].x,input.xy[i].y,best[th_id].xy[j].x,best[th_id].xy[j].y)){
                    best[th_id].xy.erase(best[th_id].xy.begin()+ j); // x
                    // best[th_id].y.erase(best[th_id].y.begin()+ j); // y
                    best[th_id].name.erase(best[th_id].name.begin()+ j); // name

                }
            }
        }
    }  // end for






    // int num_core_merge = num_cores/2; 
    // #pragma omp parallel num_threads( num_cores )
    // {
    // auto const xyz = omp_get_thread_num();  // 0 or 1
    // merge(best[xyz* 2],best[xyz*2+1]);
    // }


    return "Test";

    // std::string ret;   // save return value
    // for(auto i=0u;i<best.name.size();i++){
    
    //     ret = ret + best.name[i] +" ";

    // }
    // ret =ret+"\n";
    // return ret;


} // End func


/// ----------------Parallel End---------------------------------/




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