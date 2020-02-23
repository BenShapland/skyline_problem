#ifndef CS586_UNIQUE
#define CS586_UNIQUE

#include <cassert>		 // assert()
#include <unordered_map>
#include <iostream> 


namespace skyline {
namespace solution {
using std::vector;

bool Dominate(Node a, Node b){
    if( ((a.x < b.x)&&(a.y <= b.y)) || ((a.x <= b.x)&&(a.y < b.y))){

        return true;

    }
    return false;
}


int test(std::vector< Node > const& skyline){

    vector<Node> input = skyline;
    for(int i=0;i<input.size();i++){
        Node n =input[i];
        std::cout<<"Input "<<n.print()<<"\n";
    }
    return 0;

}

std::string solve ( std::vector< Node > const& skyline )  
{
	// assert( "Vector contains data" && ! input.empty() );
   	std::vector< Node > best;

    vector<Node> input = skyline;

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


std::string sort_solve ( std::vector< Node > const& skyline )  //const
{
    vector<Node> input = skyline;
    sort(input.begin(),input.end());

    vector<Node> best;
    best.push_back(input[0]);
    
    for (size_t i = 1; i < input.size(); i++)
    {
        if(best.back().y > input[i].y)
        {
            best.push_back(input[i]);
        }
    }


//  Testing
    // vector<Node> test = best;
    // for(int i=0;i<test.size();i++){
    //     Node n =test[i];
    //     std::cout<<"Output sort "<<n.print()<<"\n";
    // }

//
    std::string ret;   // save return value
    for(auto i=0u;i<best.size();i++){
        Node n = best[i]; 
        ret = ret + n.name +" ";
    }
    ret =ret +"\n";

    return ret;
}


} 
} 

#endif 