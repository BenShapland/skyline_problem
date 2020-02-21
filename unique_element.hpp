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
#include <Node.h>

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

// struct map_based
// {
// 	/**
// 	 * Expected O(|haystack|), depending on hash collisions. Worst case O(|haystack|^2).
// 	 * Finds the unique element by scanning the haystack and adding every
// 	 * element to a dictionary that maps elements to number of times they've been seen.
// 	 *
// 	 * This is implemented as a _template function_ using type T (similar to a Generic in Java).
// 	 * The compiler infers what type T is (e.g., an int or a float) at compile time based on 
// 	 * the arguments specified at the invocation site and auto-generates a version of this
// 	 * function that is specific to that type T. This allows us to write reusable, generic code
// 	 * while still getting the benefit of optimisations based on type. For example, we can divide
// 	 * an int by 2 by shifting right, but we cannot do that with a float.
// 	 *
// 	 * The argument is a _vector_ (called haystack), which is the dynamic array that is built into
// 	 * the C++ Standard Template Library (STL). Here is a simple tutorial: shorturl.at/dkrsZ
// 	 * The argument is a dynamic array of T's, e.g., a vector of unsigned integers.
// 	 * In particular, we are passing a const-reference; i.e., the haystack cannot be modified (the
// 	 * const keyword), and this is a reference (the & operator) to the exact same dynamic array
// 	 * as at the invocation site. The return type is also of type T, i.e., the same as the elements
// 	 * of the dynamic array.
// 	 */
// 	template < typename T >
// 	T operator() ( std::vector< T > const& haystack ) const
// 	{
// 		// We are assuming that the input cannot be empty. Nobody should ever pass an empty
// 		// vector to this function, or the behaviour is "undefined". This assert() is a run-time
// 		// test to ensure this assumption is valid. What is unique about the assert() library is
// 		// that the code is only run when we are debugging (specifically, creating a Debug build);
// 		// when we run for performance (create a Release build), this code is stripped out by the
// 		// compiler. Thus we get the documentation of the constraint (test-as-documentation), and
// 		// run the test when we want to test correctness, but it doesn't impact performance in
// 		// production. The argument is a boolean predicate: if true, code continues; if false, an
// 		// interrupt is triggered and the program crashes with debug information printed to the
// 		// console. I've used a "trick" in that a string is always _true_ in c/c++, so the below
// 		// expression is equivalent to ( true && ! haystack.empty() ), but now more clearly
// 		// documents the intention of this assertion.
// 		// In general, you should not use assertions for input validation (like I've done here),
// 		// but for testing invariants and post-conditions.
// 		assert( "Vector contains data" && ! haystack.empty() );

// 		// The using keyword creates an alias. In this case, Frequency is a more expressive
// 		// typename than just size_t (a built-in type indicating the size of something).
// 		using Frequency = size_t;

// 		// The c++ STL has two built-in dictionary types called map (a balanced tree) and
// 		// unordered_map (a hash map). This statement declares and initialises an empty hash map
// 		// from type T (the elements in our haystack) and Frequency (our alias to the size type). 
// 		std::unordered_map< T, Frequency > element_frequencies;

// 		// This range-based for loop iterates every element of the vector haystack,
// 		// assigning it to a scoped const-reference.
// 		// The auto keyword instructs the compiler to infer the type (in this case, T) on our
// 		// behalf. There is a lot of contention around the use of auto; I agree with Stroustrup
// 		// and Sutter that it emphasises that the type isn't important to understanding this loop.
// 		for( auto const& element : haystack )
// 		{
// 			// We check if the next element of the haystack is already in our dictionary by
// 			// comparing the number of times it exists in the dictionary to the constant literal, 0.
// 			// A dictionary can only contain an element 0 or 1 times, but this syntax is chosen in
// 			// the STL for consistency with other containers such as std::vector<>.
// 			if( element_frequencies.count( element ) > 0 )
// 			{
// 				// Element is found, so increment the frequency associated with it in the hash map
// 				++element_frequencies[ element ];
// 			}
// 			else
// 			{
// 				// New element; insert with frequency of 1.
// 				element_frequencies[ element ] = 1;
// 			}
// 		}

// 		// Finally, we scan all (key, value) element-frequency pairs of the dictionary to see
// 		// which one has a frequency of 1 and return that pair's element.
// 		// We again use the range-based for loop. Above, the loop was over a container of single
// 		// elements, but this container contains pairs. So, we use the c++17 feature structured
// 		// bindings (the square bracket notation) to bind the first and second element of the pairs
// 		// to unique scoped variables.
// 		for( auto const& [ element, frequency ] : element_frequencies )
// 		{
// 			// Note the cross-lingual _defensive programming_ trick of putting the constant
// 			// on the left-hand side. In most languages, this will throw a compiler error if you
// 			// accidentally type the assignment operator (=) rather than the equality operator (==)
// 			if( 1u == frequency )
// 			{
// 				return element;
// 			}
// 		}

// 		// If the input has a solution, this part of the code is unreachable, but we still
// 		// need to return something. We again use an assert to document this and throw an error.
// 		// Note that this is not validating a post-condition; it is validating the user input again.
// 		assert( "Vector contained no unique element!" );
// 		return haystack.front();
// 	}
// };

// /**
//  * O(|haystack|). Calculates the needle by xor'ing all values together. Exploits the
//  * property that x ^ x == 0; e.g., w ^ x ^ x ^ y ^ y ^ z ^ z == w ^ 0 ^ 0 ^ 0 == w.
//  * However, this will fail if the duplicated values appear an odd number of times.
//  * Note that this will only work on specific data types, so we don't write a template fn.
//  */
// uint32_t bit_based ( std::vector< uint32_t > const& haystack )
// {
// 	assert( "Vector contains data" && ! haystack.empty() );
// 	uint32_t result = 0u;

// 	for( auto const hay : haystack )
// 	{
// 		result ^= hay;
// 	}
// 	std::cout<<"result: "<<result <<"\n";
// 	return result;
// }


// struct sort_based
// {
// 	/**
// 	 * O(n lg n), because of the initial sort.
// 	 * Calculates result by sorting all the values and then scanning for the needle.
// 	 * We can identify the needle because both its predecessor and successor in sorted
// 	 * order differ from it.
// 	 *
// 	 * We are going to modify the haystack this time (specifically, we will sort it); so,
// 	 * we cannot accept a const argument. But we don't want to allow the method to change
// 	 * the original vector at the invocation site, so this time we pass-by-value, i.e.,
// 	 * copy it, as indicated by the absence of the reference operator (&).
// 	 */
// 	template < typename T >
// 	T operator() ( std::vector< T > haystack ) const
// 	{
// 		assert( "Vector contains data" && ! haystack.empty() );
// 		assert( "Vector does not contain exactly 2 elements" && haystack.size() != 2 );

// 		// Uses the c++ built-in sort algorithm, which is typically quicksort.
// 		// It depends on the specific compiler: c.f., https://stackoverflow.com/a/1840131/2769271
// 		std::sort( std::begin( haystack ), std::end( haystack ) );

// 		// check edge case that the needle is the smallest element in the haystack
// 		if( 1u == haystack.size() ) 			 { return haystack.front(); }
// 		if( haystack.front() != haystack[ 1u ] ) { return haystack.front(); }

// 		// otherwise scan every sorted triplet and check if the middle val is our needle
// 		// uses an iterator, it, retrieved with the .begin() and .end() functions of std::vector<>
// 		for( auto it = haystack.begin() + 1; it != haystack.end(); ++it )
// 		{
// 			if( *it != *( it - 1 ) && *it != *( it + 1 ) )
// 			{
// 				std::cout<<"it: "<< *it <<"\n";
// 				return *it;
// 			}
// 		}

// 		// Unreachable code block on well-defined input
// 		assert( "Vector contained no unique element!" );
// 		return haystack.front();
// 	}
// };



// struct two_loops
// {
// 	/**
// 	 * O(n lg n), because of the initial sort.
// 	 * Calculates result by sorting all the values and then scanning for the needle.
// 	 * Uses a dual-pointer, nested loop for the needle scan.
// 	 */
// 	template < typename T >
// 	T operator() ( std::vector< T > haystack ) const
// 	{
// 		assert( "Vector contains data" && ! haystack.empty() );
// 		assert( "Vector does not contain exactly 2 elements" && haystack.size() != 2 );

// 		std::sort( std::begin( haystack ), std::end( haystack ) );

// 		// otherwise scan each unique element to see how many successors match it
// 		auto it = haystack.cbegin();
// 		while( it != haystack.cend() )
// 		{
// 			// Advance another iterator until the end of the vector or the next unique element
// 			auto it_matches = it + 1;
// 			while( it_matches != haystack.cend() && *it == *it_matches )
// 			{
// 				++it_matches;
// 			}

// 			// Check how far the iterator went; if it didn't move, we've found our needle.
// 			if( 1u == std::distance( it, it_matches ) )
// 			{
// 				std::cout<<"it: "<< *it <<"\n";
// 				return *it;
// 			}
// 			else // otherwise, advance the main iterator it to the next unique element and repeat
// 			{
// 				it = it_matches;
// 			}
// 		}

// 		// Unreachable code block on well-defined input
// 		assert( "Vector contained no unique element!" );
// 		return haystack.front();
		
// 	}
// };


// struct skip_based
// {
// 	/**
// 	 * O(n lg n), because of the initial sort.
// 	 * Calculates result by sorting all the values and then scanning for the needle.
// 	 * Uses an increment-by-two approach to the needle scan. Works by pairing each element
// 	 * to its immediate successor, thus only needing to check each pair. However,
// 	 * like bit_based, this assumes that duplicate values appear an even number of times.
// 	 */
// 	template < typename T >
// 	T operator() ( std::vector< T > haystack ) const
// 	{
// 		// check edge case of a single-element array
// 		if( 1u == haystack.size() ) { return haystack.front(); }

// 		assert( "Vector contains data" && ! haystack.empty() );
// 		assert( "Vector does not contain exactly 2 elements" && haystack.size() != 2 );

// 		std::sort( std::begin( haystack ), std::end( haystack ) );

// 		// Conduct increment-by-two scan. Switch to index arrays rather than
// 		// iterators because we will seg fault if there are an odd number of elements
// 		// and we use iterator equality to find the end of the array.
// 		for( auto i = 0u; i < haystack.size(); i += 2 )
// 		{
// 			if( haystack[ i ] != haystack[ i + 1 ] )
// 			{
// 				// No matching pair for this element. It's our needle!
// 				std::cout<<"haystack[ i ]: "<< haystack[ i ]<<"\n";
// 				return haystack[ i ];
// 			}
// 		}

// 		// Unreachable code block on well-defined input
// 		assert( "Vector contained no unique element!" );
// 		return haystack.front();
// 	}
// };

} // namespace unique
} // namespace csc586

#endif // CS586_UNIQUE