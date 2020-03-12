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
/// -------------------------------------------------/
std::string  solve_parallel (Node const& input )  
{
    assert(input.xy.size() == input.name.size());
    
    
   	std::vector<Node>  best;  // vector of nodes

    // int num_cores =4;

    // for(int i=0;i<num_cores;i++){
    //     Node best_thread;
    //     best.push_back(best_thread);
    // }
    
    int count =0;

        #pragma omp parallel for num_threads( num_cores )

        for (auto i =0u ; i <  input.xy.size(); i++)
        { 
            
            
            // auto const th_id = omp_get_thread_num();


            count = 0;
            for(auto k = 0u; k<best[th_id].x.size(); k++){
       
                if(Dominate(best[th_id].x[k],best[th_id].y[k] ,input.x[i],input.y[i] ) || (equal(best[th_id].x[k],best[th_id].y[k], input.x[i], input.y[i])) ){
                    count --;
                    break;
                }
            }

            if(count == 0){
                best[th_id].add(input.x[i],input.y[i],input.name[i] );  // Best Updated fukkkk
              
                for(auto j = 0u; j<best[th_id].x.size(); j++){
                    if(Dominate(input.x[i],input.y[i],best[th_id].x[j],best[th_id].y[j])){
                        best[th_id].x.erase(best[th_id].x.begin()+ j); // x
                        best[th_id].y.erase(best[th_id].y.begin()+ j); // y
                        best[th_id].name.erase(best[th_id].name.begin()+ j); // name

                    }
                }
            }
        }
   


    // Node combine;
    // combine.x.reserve( best[0].x.size() + best[1].x.size() ); // preallocate memory
    // combine.x.insert( combine.x.end(), best[0].x.begin(), best[0].x.end() );
    // combine.x.insert( combine.x.end(), best[1].x.begin(), best[1].x.end() );

    // combine.y.reserve( best[0].y.size() + best[1].y.size() ); // preallocate memory
    // combine.y.insert( combine.y.end(), best[0].y.begin(), best[0].y.end() );
    // combine.y.insert( combine.y.end(), best[1].y.begin(), best[1].y.end() );

    // combine.name.reserve( best[0].name.size() + best[1].name.size() ); // preallocate memorname
    // combine.name.insert( combine.name.end(), best[0].name.begin(), best[0].name.end() );
    // combine.name.insert( combine.name.end(), best[1].name.begin(), best[1].name.end() );

    // Node combine1;
    // combine1.x.reserve( best[2].x.size() + best[3].x.size() ); // preallocate memory
    // combine1.x.insert( combine1.x.end(), best[2].x.begin(), best[2].x.end() );
    // combine1.x.insert( combine1.x.end(), best[3].x.begin(), best[3].x.end() );

    // combine1.y.reserve( best[2].y.size() + best[3].y.size() ); // preallocate memory
    // combine1.y.insert( combine1.y.end(), best[2].y.begin(), best[2].y.end() );
    // combine1.y.insert( combine1.y.end(), best[3].y.begin(), best[3].y.end() );

    // combine1.name.reserve( best[2].name.size() + best[3].name.size() ); // preallocate memorname
    // combine1.name.insert( combine1.name.end(), best[2].name.begin(), best[2].name.end() );
    // combine1.name.insert( combine1.name.end(), best[3].name.begin(), best[3].name.end() );


    // Node combine2;

    // combine2.x.reserve( best[4].x.size() + best[5].x.size() ); // preallocate memory
    // combine2.x.insert( combine2.x.end(), best[4].x.begin(), best[4].x.end() );
    // combine2.x.insert( combine2.x.end(), best[5].x.begin(), best[5].x.end() );

    // combine2.y.reserve( best[4].y.size() + best[5].y.size() ); // preallocate memory
    // combine2.y.insert( combine2.y.end(), best[4].y.begin(), best[4].y.end() );
    // combine2.y.insert( combine2.y.end(), best[5].y.begin(), best[5].y.end() );

    // combine2.name.reserve( best[4].name.size() + best[5].name.size() ); // preallocate memorname
    // combine2.name.insert( combine2.name.end(), best[4].name.begin(), best[4].name.end() );
    // combine2.name.insert( combine2.name.end(), best[5].name.begin(), best[5].name.end() );

    // Node combine0_1;
    // combine0_1.x.reserve( combine.x.size() + combine1.x.size() ); // preallocate memory
    // combine0_1.x.insert( combine0_1.x.end(), combine.x.begin(), combine.x.end() );
    // combine0_1.x.insert( combine0_1.x.end(), combine1.x.begin(), combine1.x.end() );

    // combine0_1.y.reserve( combine.y.size() + combine1.y.size() ); // preallocate memory
    // combine0_1.y.insert( combine0_1.y.end(), combine.y.begin(), combine.y.end() );
    // combine0_1.y.insert( combine0_1.y.end(), combine1.y.begin(), combine1.y.end() );

    // combine0_1.name.reserve( combine.name.size() + combine1.name.size() ); // preallocate memorname
    // combine0_1.name.insert( combine0_1.name.end(), combine.name.begin(), combine.name.end() );
    // combine0_1.name.insert( combine0_1.name.end(), combine1.name.begin(), combine1.name.end() );



    // Node out;

    // out.x.reserve( combine0_1.x.size() + combine2.x.size() ); // preallocate memory
    // out.x.insert( out.x.end(), combine0_1.x.begin(), combine0_1.x.end() );
    // out.x.insert( out.x.end(), combine2.x.begin(), combine2.x.end() );

    // out.y.reserve( combine0_1.y.size() + combine2.y.size() ); // preallocate memory
    // out.y.insert( out.y.end(), combine0_1.y.begin(), combine0_1.y.end() );
    // out.y.insert( out.y.end(), combine2.y.begin(), combine2.y.end() );


    // out.name.reserve( combine0_1.name.size() + combine2.name.size() ); // preallocate memorname
    // out.name.insert( out.name.end(), combine0_1.name.begin(), combine0_1.name.end() );
    // out.name.insert( out.name.end(), combine2.name.begin(), combine2.name.end() );


   
    // }

    // return solve(out);

} 

// ---------------------------------------------------// 

// std::string  solve_parallel (Node const& input,Node const& input2 )  
// {
  





	
// }






} 
}
#endif 