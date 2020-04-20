
#include <iostream> // for outputting (printing) to streams (e.g., the terminal)
#include <random> 	// std::rand, std::srand, std::default_random_engine
#include <cmath>	// sqrt()
#include "timing.hpp"
#include <sstream>
#include "./solution.hpp"

using std::vector;

// The random string generator to name each node 
// https://github.com/InversePalindrome/Blog/blob/master/RandomString/RandomString.hpp
std::string random_string(std::size_t length)
{
    const std::string characters = "abcdefghijklmnopqrstuvwxyz";

    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(0, characters.size() - 1);

    std::string random_string;

    for (std::size_t i = 0; i < length; ++i)
    {
        random_string += characters[distribution(generator)];
    }

    return random_string;
}


template < typename RandomGenerator >
	auto build_rand_vec( RandomGenerator gen, size_t const size )
	{
		std::vector< decltype((gen)()) > random_data( size );
		std::generate( random_data.begin(), random_data.end(), gen );

		return random_data;
	}


struct skyline_vec
{

	public:
		int n;
	skyline_vec(int a){
		n=a;
	}

	std::vector< Node > operator() () const
	{
		// Declare the vector that we want to produce and indicate the amount of space it will use.
		std::vector< Node > vec;
		
		// push one unique random val onto vector
		// or'ing with 1 ensures the value (used as a multiplier below) cannot be zero, by setting
		// the least significant bit

		for( int i = 0u; i < n; ++i )
		{
			// create random val and push it twice onto vector
			// by cancelling the least significant bit, we guarantee it does not match our unique value
			auto const x = ( std::rand()  & ~1u );
			auto const y = ( std::rand()  & ~1u );
			std::string name = random_string(4);//giving it a random length of 4	
			vec.push_back( Node(x,y,name) );
		}


		return vec;
	}
};


/**
 * The function that is run when the application is launched. In this case, runs our benchmarks.
 */
int main(int argc, char** argv)
{
 	int number_nodes=5000;   // default value
	if(argc ==2){
		std::istringstream a1(argv[1]);
		a1>>number_nodes;
	}

	auto const num_test_instances = 50;  
	std::srand ( static_cast< uint32_t >( std::time(0) ) );


	// Create consistent random data to use with each algorithm/implementation.
	auto const random_data = build_rand_vec( skyline_vec{number_nodes}
										   , num_test_instances
										   );
	std::cout << "-------------------Brute Force (output) --------------------------\n";
	auto const time_solve = timing::benchmark::benchmark( skyline::solution::solve,  random_data );
	std::cout << "-------------------Sort (output)  --------------------------\n";
	auto const time_sort = timing::benchmark::benchmark( skyline::solution::sort_solve,  random_data );

	std::cout << "Average time per call BRUTE FORCE = " << time_solve    << " us" << std::endl;
	std::cout << "Average time per call SORT based  = " << time_sort    << " us" << std::endl;

	return 0;
}