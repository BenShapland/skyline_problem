/**
 * Timing library to benchmark and comparatively analyse different implementation approaches
 */

#ifndef CS586_TIMING
#define CS586_TIMING

#include <algorithm> // std::for_each()
#include <chrono>	 // timing libraries
#include <iostream> // for outputting (printing) to streams (e.g., the terminal)
#include "./Node.h"
#include <typeinfo>       // operator typeid

namespace timing {
namespace benchmark {

using duration = float;


template < typename Callable, typename Container >
	duration benchmark( Callable f, Container test_instances )
	{


		// Same benchmarking code is used for multiple solutions.
		// Since we cannot predefine output type, set used this func to detect output type
		using output_type = decltype( f( test_instances.front() ) );


		// Use need to capture output in order to prevent a benchmarking result of 0 nano secs
		output_type output;
	

		// start timer
		auto const start_time = std::chrono::steady_clock::now();

		// run function f on every random test instance, arbitrarily summing the return values.
		
		std::for_each( std::cbegin( test_instances )
					 , std::cend  ( test_instances )
					 , [&output, f]( auto const& v ){
						 

							output = output + f(v); // caputure return value and append it to output
						 
						 } );


		// end timer
		auto const end_time = std::chrono::steady_clock::now();

		// Print output
		std::cout<< "output from benchmark: "<< output;
		std::cout<< "\n";

	
		// return average time
		// the syntax for this library is a bit cumbersome...
		return std::chrono::duration_cast<std::chrono::microseconds>( end_time - start_time ).count()
			/ static_cast< duration >( test_instances.size() );
	}


} // namespace benchmark
} // namespace csc586

#endif // CS586_TIMING