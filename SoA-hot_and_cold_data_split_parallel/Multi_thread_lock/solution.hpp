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
                best.add(input.xy[i].x,input.xy[i].y,input.name[i] );  
                // count_best +=1;
                // update = true;
              
                for(auto j = 0u; j<best.xy.size(); j++){
                    if(Dominate(input.xy[i].x,input.xy[i].y,best.xy[j].x,best.xy[j].y)){
                        best.xy.erase(best.xy.begin()+ j); // x
                        // best.y.erase(best.y.begin()+ j); // y
                        best.name.erase(best.name.begin()+ j); // name

                    }
                }

            } //  Input Dom all of best
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
    
    // std::cout<<"Starting";
    int size_best = 1000;
    std::vector<XY> values;
    values.reserve(size_best);
    // values.size(); //returns 0
    // std::cout<<"values.size before: "<<values.size()<<"\n";


    std::vector<std::string> n;
    n.reserve(size_best);
    n.size(); //returns 0

    Node best;
    best.xy = values;
    best.name = n;

    // int written =0;
    // int dom =0;

// // Init locks in array lock
//     omp_lock_t lock[size_best];
//     for (int i=0; i<size_best; i++)
//         omp_init_lock(&(lock[i]));


    // parallel
    // #pragma omp parallel for num_threads( num_cores )
    // #pragma omp parallel for num_threads(  1) shared(best, lock, input) default(none)
    for (auto i =0u ; i <  input.xy.size(); i++) 
    {

        int written = 0;  
        int dom =0;
        // // auto const th_id = omp_get_thread_num(); 

        for(auto k = 0u; k<best.xy.size(); k++){  // compare input and best


            // if index best locked -> wait 
            // else we continue
    
            if(Dominate(input.xy[i].x,input.xy[i].y,  best.xy[k].x,best.xy[k].y  ) ){  // Input Dominate Best ->  Good input -> Save it
                // lock best[k]


                // write input[i] to best[k]
                // best.xy[k] = input.xy[i]; ?
                best.xy[k].x = input.xy[i].x;
                best.xy[k].y = input.xy[i].y;
                best.name[k] = input.name[i];


                written = 1;
                // break;

            }

            // dominate * dom ??
            else if(Dominate(best.xy[k].x,best.xy[k].y,input.xy[i].x,input.xy[i].y ))  // Best dominate Input -> Input not needed
            {
                dom = 1;
                break;
            }


        } // loop best


                     

        if(dom==0   && written==0){

        //     // lock best.size(-1)
        //     std::cout<<"best.size before: "<<best.xy.size();
            best.add(input.xy[i].x,input.xy[i].y,input.name[i] );  
        //     std::cout<<"best.size after: "<<best.xy.size()<<"\n";
        //     // best.xy[best.xy.size()-1] = input.xy[i];
        //     // best.name[best.name.size()-1] = input.name[i];

        //     // unlock

        }




    } // for input

    
    assert(best.xy.size() == best.name.size());

    // Need to Remove Duplicates
    






    std::string ret;   // save return value
    for(auto i=0u;i<best.name.size();i++){
        ret = ret + best.name[i] +" ";

    }
    ret =ret+"\n";
    return ret;



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