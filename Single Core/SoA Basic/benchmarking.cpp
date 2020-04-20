
#include <iostream> // for outputting (printing) to streams (e.g., the terminal)
#include <random> 	// std::rand, std::srand, std::default_random_engine
#include <cmath>	// sqrt()
#include <sstream>
#include "timing.hpp"


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

/**
 * Creates and returns a vector pre-populated by repeatedly calling gen size times.
 *
 * see timing.hpp for a description of functors (e.g., gen). size_t is the built-in
 * type that refers to the size of things. On most architectures, it is a 64-bit
 * unsigned integer.
 *
 * Note the use of auto as a return type. This is not standard c++ (but should and will be).
 * You may need to use decltype() if using the clang compiler instead of g++. It automatically
 * deduces the return type of the function based on the return statement.
 */
template < typename RandomGenerator >
	auto build_rand_vec( RandomGenerator gen, size_t const size )
	{
		// see timing.hpp for a description of decltype().
		// Initialises a vector with the appropriate size, in which we will create the random data.
		std::vector< decltype((gen)()) > random_data( size );

		// std::generate() = STL. This could be done with a loop from 0,...,size, calling gen() each
		// iteration. See https://www.fluentcpp.com/2017/01/05/the-importance-of-knowing-stl-algorithms/
		// for a compelling discussion of why using STL algorithms like this is better than explicit loops.
		// Spoiler: it better self-documents (in code) intent and is less prone to off-by-one-errors.
		// For an explanation of syntax, see the use of std::for_each() in timing.hpp
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

	Node  operator() () const
	{
		// Declare the vector that we want to produce and indicate the amount of space it will use.
	
	
		// push one unique random val onto vector
		// or'ing with 1 ensures the value (used as a multiplier below) cannot be zero, by setting
		// the least significant bit
		Node nn;
		for( int i = 0u; i < n; ++i )
		{
			auto const x = ( std::rand() & ~1u );
			auto const y = ( std::rand() & ~1u );
			std::string name = random_string(4);//giving it a random length of 4
			nn.add(x,y,name);  // To add to SoC data struct
		}

		return nn ;
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

	// For random numbers, one must first seed the random number generator. This is the idiomatic
	// approach for the random number generator libraries that we have chosen.
	std::srand ( static_cast< uint32_t >( std::time(0) ) );

	// // Run the sanity-check benchmark.
	// mwe_benchmark();

	// Create consistent random data to use with each algorithm/implementation.
	auto const random_data = build_rand_vec( skyline_vec{number_nodes}
										   , num_test_instances
										   );
	auto const time = timing::benchmark::benchmark( skyline::solution::solve,  random_data );


	std::cout << "Average time per call brute force     = " << time     << " us" << std::endl;


	return 0;
}