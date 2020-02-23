#ifndef CS586_UNIQUE
#define CS586_UNIQUE

#include <cassert>		 // assert()
#include <unordered_map>
#include <iostream> 


namespace skyline {
namespace solution {
using std::vector;

bool Dominate(Node a, Node b){
    if( ((a.x > b.x)&&(a.y >= b.y)) || ((a.x >= b.x)&&(a.y > b.y))){

        return true;

    }
    return false;
}

std::string solve ( std::vector< Node > const& input )  
{
	assert( "Vector contains data" && ! input.empty() );
   	std::vector< Node > best;


    bool update = true;
    int count =0;
    while(update){
        for (auto i =0u ; i < input.size(); i++)
        { 
            update = false;
            count = 0;
            for(auto k = 0u; k<best.size(); k++){
                //if nothing dominates input
                //add it to best
                if(Dominate(best[k],input[i]) || (equal(best[k], input[i])) ){
                    count --;
                }
            }
            if(count == 0){
                best.push_back(input[i]);
                // input[i].print();
                update = true;
                
            }
            //if any input doms any of best
            //add it and remove what it doms
            for(auto j = 0u; j<best.size(); j++){
                if(Dominate(input[i],best[j])){
                    best.erase(best.begin()+ j);
                }
            }
        }
    }


    std::string ret;   // save return value
    for(auto i=0u;i<best.size();i++){
        Node n = best[i]; 
        ret = ret + n.name +" ";

    }
    ret =ret+"\n";

    return ret;

	
}


} 
} 

#endif 