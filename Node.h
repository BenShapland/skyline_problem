#include <iostream> 

class Node
{
    public:
        int x,y;
        std::string name;
    Node(){
        x = 0;
        y = 0;
        name = "I was born NAME-LESS";
    }
	Node(int a ,int b, std::string c){
		x=a;
		y=b;
		name=c;
    }
    void jumble(){
        srand(time(NULL));
        x= rand() % 100;
        y= rand() % 100;
    }
    std::string print(){
        std::string out = name + " (" + std::to_string(x) + "," + std::to_string(y) + ")";
        return out;
    }
    void set(int a, int b, std::string c){
        x=a;
        y=b;
        name = c;
    }
};

bool equal(Node a, Node b){
    if(a.x == b.x){
        if(a.y == b.y){
            if(a.name == b.name){
                return true;
            }
        }
    }
    return false;
}