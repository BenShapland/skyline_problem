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
#include "./Node.h"

// Namespaces are similar to _packages_ in Java. They group code into (nested) groups.
// It has a function both of documentating system architecture and of avoiding name clashes.
// They are not necessary, but very helpful and generally good practice.
// For more information, consult https://docs.microsoft.com/en-us/cpp/cpp/namespaces-cpp?view=vs-2019
namespace csc586 {
namespace unique {
using std::vector;


// [X1,Y1,X2,Y2,.......,Xn,Yn]
// 
uint32_t BENS ( std::vector< Node > const& haystack ) //might need return some node or a list of strings 
{
	assert( "Vector contains data" && ! haystack.empty() );
	uint32_t result = 0u;
	// std::cout<<"IN BENS";
	std::cout<< "  number of elements: " << haystack.size()<<"\n";
	for( auto const hay : haystack )
	{
		result++;
	}
	std::cout<<"result: "<<result <<"\n";
	return result;
}


} // namespace unique
} // namespace csc586

#endif // CS586_UNIQUE