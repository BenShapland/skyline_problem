
// Simple C++ program to display "Hello World" 
  
#include<iostream>  
#include<vector>
#include<random>
#include <ctime>
#include <cstdlib>
// #include <array>
#include <algorithm>    // std::sort

#include "./Node.h"

using namespace std; 
using std::vector;


//dominating - has greater x and or y 
//not looking at equal cases 
bool Dominate(Node a, Node b){
    if( ((a.x < b.x)&&(a.y <= b.y)) || ((a.x <= b.x)&&(a.y < b.y))){
        // a.print();
        // b.print();
        return true;

    }
    // cout<<"NO DOM";
    return false;
}

vector<Node> Solve(vector<Node> input){
    vector<Node> best;
    // best.push_back(input[0]);

    cout<< "\n"<<input.size()<<"\n";
    int size = input.size();
    bool update = true;
    int count =0;
    while(update){
        for (int i =0 ; i < size; i++)
        { 
            update = false;
            count = 0;
            for(int k = 0; k<best.size(); k++){
                //if nothing dominates input
                //add it to best
                if(Dominate(best[k],input[i]) || (equal(best[k], input[i])) ){
                    count --;
                }
            }
            if(count == 0){
                best.push_back(input[i]);
                input[i].print();
                update = true;
                
            }
            //if any input doms any of best
            //add it and remove what it doms
            for(int j = 0; j<best.size(); j++){
                if(Dominate(input[i],best[j])){
                    best.erase(best.begin()+ j);
                }
            }
        }
    }
    return best;
}

struct less_than_key
{
    inline bool operator() (const Node& struct1, const Node& struct2)
    {
        if(struct1.x == struct2.x){
            return (struct1.y < struct2.y);
        }
        return (struct1.x < struct2.x);
    }
};


vector<Node> sortSolve(vector<Node> input){
    
    sort(input.begin(),input.end(),less_than_key());
    vector<Node> best;
    best.push_back(input[0]);
    
    for (size_t i = 1; i < input.size(); i++)
    {
        if(best.back().y >input[i].y)
        {
            best.push_back(input[i]);
        }
    }
    


    return best;

}



/*
 * Simple main function:
 * Read two numbers and write their sum
 */  
int main() 
{ 

    vector<Node> skyline_paper;
    skyline_paper.push_back(Node(1,12,"a"));
    skyline_paper.push_back(Node(2,7,"b"));
    skyline_paper.push_back(Node(4,22,"c"));
    skyline_paper.push_back(Node(5,14,"d"));
    skyline_paper.push_back(Node(6,5,"e"));
    skyline_paper.push_back(Node(8,19,"f"));
    skyline_paper.push_back(Node(9,9,"g"));
    skyline_paper.push_back(Node(10,4,"h"));
    skyline_paper.push_back(Node(12,13,"i"));
    skyline_paper.push_back(Node(15,15,"j"));
    skyline_paper.push_back(Node(15,22,"k"));
    skyline_paper.push_back(Node(16,6,"l"));
    skyline_paper.push_back(Node(17,10,"m"));
    skyline_paper.push_back(Node(17,20,"n"));
    skyline_paper.push_back(Node(21,3,"0"));
    skyline_paper.push_back(Node(22,14,"p"));


    // cout<<"pre solution"<< skyline_paper.back().name;
    // cout<< "\n"<<sizeof(skyline_paper)/sizeof(skyline_paper[0])<<"\n";
    
    // shuffle( skyline_paper.begin(), skyline_paper.end(), default_random_engine{} );

    vector<Node> solution= sortSolve(skyline_paper);

    
    for (int i = 0; i < solution.size(); i++)
    {
        cout<<"out of solution: "<<solution.size();
        cout<<solution[i].print() << "\n";
    }

    vector<Node> sol= Solve(skyline_paper);

    
    for (int i = 0; i < sol.size(); i++)
    {
        cout<<"out of solution: "<<sol.size();
        cout<<sol[i].print() << "\n";
    }

    


    return 0; 
} 
