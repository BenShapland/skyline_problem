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

    std::string print(){
        std::string out = name + " (" + std::to_string(x) + "," + std::to_string(y) + ")";
        return out;
    }

    void set(int a, int b, std::string c){
        x=a;
        y=b;
        name = c;
    }
    
    // bool operator < (const Node& str) const
    bool operator < (const Node& str)const

    {
        if(x == str.x){
            return (y < str.y);
        }
        return (x < str.x);
    }
};

bool equal(Node a, Node b){
    if(a.x == b.x){
        if(a.y == b.y){
            // if(a.name == b.name){   // Test name also - better cache without
                return true; 
            // }
        }
    }
    return false;
}