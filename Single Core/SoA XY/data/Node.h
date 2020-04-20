#include <iostream> 

class XY{

    public:
        int x;
        int y;


    XY(){
    }


    XY(int a ,int b){
        x = a;
        y = b;
    }

    // bool dominates(XY other){
    //     if( ((x < other.x)&&(y <= other.y))
    //      || ((x <= other.x)&&(y < other.y))){
    //         return true;
    //     }
    //     return false;
    // }

};
// a.dom(b)



class Node
{
    public:
        //  use a vector of nodexy
        // std::vector<int> x;
        // std::vector< int > y;
        std::vector< XY > xy;
        std::vector< std::string > name;
        

    Node(){
    
    }

    void add(int a,int b,std::string c){
    
        xy.push_back(XY(a,b));
        name.push_back(c);

    }

    void print_node(){

        std::string ret_xy = "";
        int name_size =name.size();
        for (int i=0; i<name_size;i++)
        {
            ret_xy = ret_xy + name[i] + " ";

        }
        std::cout<<ret_xy;

    }

};



bool equal(int x1,int y1, int x2,int y2 ){

    if( (x1 == x2) && (y1== y2 ))
        return true;

    return false;
}
