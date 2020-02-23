#ifndef CS586_UNIQUE
#define CS586_UNIQUE

#include <cassert>		 // assert()
#include <unordered_map>
#include <iostream> 


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
    assert(input.x.size() == input.y.size());
    assert(input.x.size()== input.name.size());
    

   	Node best;
    
    bool update = true;
    int count =0;

    while(update){
        for (auto i =0u ; i <  input.x.size(); i++)
        { 
            update = false;
            count = 0;
            for(auto k = 0u; k<best.x.size(); k++){
                // if nothing dominates input
                //add it to best
                if(Dominate(best.x[k],best.y[k] ,input.x[i],input.y[i] ) || (equal(best.x[k],best.y[k],best.name[k], input.x[i], input.y[i], input.name[i] )) ){
                    count --;
                }
            }
            if(count == 0){
                best.add(input.x[i],input.y[i],input.name[i] );
                // input[i].print();
                update = true;
                //if any input doms any of best
                //add it and remove what it doms
                for(auto j = 0u; j<best.x.size(); j++){
                    if(Dominate(input.x[i],input.y[i],best.x[j],best.y[j])){
                        best.x.erase(best.x.begin()+ j); // x
                        best.y.erase(best.y.begin()+ j); // y
                        best.name.erase(best.name.begin()+ j); // name

                    }
                }
            }
        }
    }


    std::string ret;   // save return value


    for(auto i=0u;i<best.name.size();i++){
     
        ret = ret + best.name[i] +" ";

    }
    ret =ret+"\n";

    return ret;

	
}


} 
} 

#endif 