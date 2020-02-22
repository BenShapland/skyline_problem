/**
 * Various methods designed by the CSC 485/586 students for finding the
 * single unique element (needle) in a container (haystack).
 *
 * Note that we have defined all this logic inside a header (i.e., .hpp or .h) file instead
 * of an implementation (i.e., .cpp) file because we are using templates.
 * For a deeper explanation, consult: https://stackoverflow.com/q/495021/2769271
 */

// The following two lines (combined with the last line of the file) are _include guards_.
// They ensure that in more complex applications you will not include the same file more than once.
// Most IDE's auto-generate them for you.
// The include guard identifier (in this case, "CS586_UNIQUE") is unique for every header.
#ifndef CS586_UNIQUE
#define CS586_UNIQUE

#include <cassert>		 // assert()
#include <unordered_map>
#include <iostream> 
// #include "./Node.h"

// Namespaces are similar to _packages_ in Java. They group code into (nested) groups.
// It has a function both of documentating system architecture and of avoiding name clashes.
// They are not necessary, but very helpful and generally good practice.
// For more information, consult https://docs.microsoft.com/en-us/cpp/cpp/namespaces-cpp?view=vs-2019
namespace csc586 {
namespace unique {
using std::vector;

bool Dominate(Node a, Node b){
    if( ((a.x > b.x)&&(a.y >= b.y)) || ((a.x >= b.x)&&(a.y > b.y))){
        // a.print();
        // b.print();
        return true;

    }
    // cout<<"NO DOM";
    return false;
}

// [X1,Y1,X2,Y2,.......,Xn,Yn]
// 
 std::vector <Node>  BENS ( std::vector< Node > const& input ) //might need return some node or a list of strings 
// std::string BENS ( std::vector< Node > const& input ) //might need return some node or a list of strings 

{
	assert( "Vector contains data" && ! input.empty() );
   	std::vector< Node > best;
    // best.push_back(input[0]);

    // cout<< "\n"<<input.size()<<"\n";
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
                // input[i].print();
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
	//best
    return best;
    // return "fucktor";

	
}


} // namespace unique
} // namespace csc586

#endif // CS586_UNIQUE