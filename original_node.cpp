
// Simple C++ program to display "Hello World" 
  
#include<iostream>  
#include<vector>
#include<random>
#include <ctime>
#include <cstdlib>
#include <array>

#include "./Node.h"

using namespace std; 
using std::vector;

// class Node
// {
//     public:
//         int x,y;
//         string name;
//     Node(){
//         x = 0;
//         y = 0;
//         name = "I was born NAME-LESS";
//     }
//     Node(int a ,int b, string c){
//         x=a;
//         y=b;
//         name=c;
//     }
//     void jumble(){
//         srand(time(NULL));
//         x= rand() % 100;
//         y= rand() % 100;
//     }
//     void print(){
//         cout<<name<<"("<<x<<","<<y<<")"<< '\n';
//     }
//     void set(int a, int b, string c){
//         x=a;
//         y=b;
//         name = c;
//     }
// };
// bool equal(Node a, Node b){
//     if(a.x == b.x){
//         if(a.y == b.y){
//             if(a.name == b.name){
//                 return true;
//             }
//         }
//     }
//     return false;
// }
//dominating - has greater x and or y 
//not looking at equal cases 
bool Dominate(Node a, Node b){
    if( ((a.x > b.x)&&(a.y >= b.y)) || ((a.x >= b.x)&&(a.y > b.y))){
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


/*
 * Simple main function:
 * Read two numbers and write their sum
 */  
int main() 
{ 

    // Node start;
    // start.x = 10;
    // start.y = 69;
    // cout<<"X is: "<< start.x << "\n";
    // cout<<"Y is: "<< start.y << "\n";

    // Node other;
    // other.jumble();
    // cout<<"X is: "<< other.x << "\n";
    // cout<<"Y is: "<< other.y << "\n";

    // Node All_points[2] = {start, other};
    // cout<<"X is: "<< All_points[0].x << "\n";
    

    //simple test
    // int test_size = 10;
    // Node Node_array[test_size];
    // for(int i =0; i <test_size; i++){
    //     Node_array[i].jumble();
    // }
    // cout<<"X is: "<< Node_array[4].x << "\n";
    cout<<Node(10,69,"yeet").name;

    // Node skyline_paper[16];
    // skyline_paper[0].set(1,12,"a");
    // skyline_paper[1].set(2,7,"b");
    // skyline_paper[2].set(3,22,"c");
    // skyline_paper[3].set(5,14,"d");
    // skyline_paper[4].set(6,12,"e");
    // skyline_paper[5].set(8,19,"f");
    // skyline_paper[6].set(9,9,"g");
    // skyline_paper[7].set(10,4,"h");
    // skyline_paper[8].set(12,13,"i");
    // skyline_paper[9].set(15,15,"j");
    // skyline_paper[10].set(15,22,"k");
    // skyline_paper[11].set(16,6,"l");
    // skyline_paper[12].set(17,10,"m");
    // skyline_paper[13].set(17,20,"n");
    // skyline_paper[14].set(21,3,"0");
    // skyline_paper[15].set(22,14,"p");
    
    
    vector<Node> skyline_paper;
    skyline_paper.push_back(Node(1,12,"a"));
    skyline_paper.push_back(Node(2,7,"b"));
    skyline_paper.push_back(Node(3,22,"c"));
    skyline_paper.push_back(Node(5,14,"d"));
    skyline_paper.push_back(Node(6,12,"e"));
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


    // skyline_paper[8].print();
    cout<<"pre solution";
    cout<< "\n"<<sizeof(skyline_paper)/sizeof(skyline_paper[0])<<"\n";

    vector<Node> solution= Solve(skyline_paper);

    
    for (int i = 0; i < solution.size(); i++)
    {
        cout<<"out of solution: "<<solution.size();
        solution[i].print();
    }
    

    


    return 0; 
} 
