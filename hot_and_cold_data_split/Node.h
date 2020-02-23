#include <iostream> 

class Node
{
    public:
     
        std::vector<int> x;
        std::vector< int > y;
        std::vector< std::string > name;
        

    Node(){
    
    }


    void add(int a,int b,std::string c){
        x.push_back(a);
        y.push_back(b);
        name.push_back(c);

    }

};

bool equal(int x1,int y1, std::string n1, int x2,int y2, std::string n2 ){

    if( (x1 == x2) && (y1== y2 )  ) //&& (n1== n2 )
        return true;

    return false;
}




