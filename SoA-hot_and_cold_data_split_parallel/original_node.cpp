#include<iostream>  
#include<vector>
#include<random>
#include <ctime>
#include <cstdlib>
#include <array>
#include <cassert>		 // assert()


#include "./Node.h"

using namespace std; 
using std::vector;


// ------------------------------------------------------------------------------------//


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
    //             //add it to best
                if(Dominate(best.x[k],best.y[k] ,input.x[i],input.y[i] ) || (equal(best.x[k],best.y[k],best.name[k], input.x[i], input.y[i], input.name[i] )) ){
                    count --;
                }
            }
            if(count == 0){
                best.add(input.x[i],input.y[i],input.name[i] );
                // input[i].print();
                update = true;
    //         //if any input doms any of best
    //         //add it and remove what it doms
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



// --------------------------------------------------------------------// 


/*
 * Simple main function:
 * Read two numbers and write their sum
 */  
int main() 
{ 

    Node skyline_paper;
    skyline_paper.add(1,12,"a");
    skyline_paper.add(2,7,"b");
    skyline_paper.add(4,22,"c");
    skyline_paper.add(5,14,"d");
    skyline_paper.add(6,5,"e");
    skyline_paper.add(8,19,"f");
    skyline_paper.add(9,9,"g");
    skyline_paper.add(10,4,"h");
    skyline_paper.add(12,13,"i");
    skyline_paper.add(15,15,"j");
    skyline_paper.add(15,22,"k");
    skyline_paper.add(16,6,"l");
    skyline_paper.add(17,10,"m");
    skyline_paper.add(17,20,"n");
    skyline_paper.add(21,3,"0");
    skyline_paper.add(22,14,"p");


    // cout<<"pre solution";
    // cout<< "\n"<<sizeof(skyline_paper)/sizeof(skyline_paper[0])<<"\n";

    std::string ans = solve(skyline_paper);
    std::cout<< ans;


    


    return 0; 
} 
