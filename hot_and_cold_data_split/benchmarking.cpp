
#include <iostream> // for outputting (printing) to streams (e.g., the terminal)
#include <random> 	// std::rand, std::srand, std::default_random_engine
#include <cmath>	// sqrt()
#include "timing.hpp"

#include "./solution.hpp"



using std::vector;

// The random string generator to name each node 
// https://github.com/InversePalindrome/Blog/blob/master/RandomString/RandomString.hpp
std::string random_string(std::size_t length)
{
    const std::string characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

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


/**
 * A simple minimal working example (MWE) to test our timing benchmark. Starting with an MWE is good
 * practice in general, but we did not have time in class. This one simply calculates the square root
 * of one value.
 */
void mwe_benchmark()
{
	// Oh God! Magic numbers!! (I don't want to introduce command line arguments yet.)
	// This is number of test instances that we will pass to build_rand_vec().
	// If you *must* use magic numbers, at least define them as constants rather than literals.
	auto const n = 10000000u;

	// Here we make extensive use of lambdas to create the input parameters for benchmark() in timing.hpp.
	// The first lambda creates a functor on the fly that we will benchmark: we are benchmarking the built-in
	// square root function.
	// The random test instances that we create are just single values, generated with the built-in random
	// generator that produces non-negative values. By providing that lambda to build_rand_vec, we get n
	// random, non-negative values on which to test the sqrt() function's performance.
	auto const avg_time = timing::benchmark::benchmark ( []( uint32_t const val ){ return sqrt( val ); }
													   , build_rand_vec(
															[]() {
															   	return static_cast< uint32_t >( std::rand() );
															}
															, n )
													   );

	// This is the standard way to do output in C++. std::cout is the standard output stream
	// (usually the terminal, unless you change it). The << (stream) operator appends the right-hand
	// argument to the left-hand argument as is evaluated left-to-right. So, we append to the
	// standard output stream, this string literal, followed by the avg_time variable, followed by
	// another string literal, and finally the endline character(s). Using std::endl is more robust
	// than the newline character, because the compiler adapts to the current locale, i.e., whether
	// you also need a carriage return or not.
	std::cout << "Average time per mwe function call = " << avg_time << " us" << std::endl;
}


/**
 * Generates a random vector of data for our Lone Unique Value (LUV) problem.
 *
 * Note that it is implemented as a functor rather than a function so that we can pass it easily
 * to our generic benchmark() function in timing.hpp. It is a functor class because we have overloaded
 * the function call operator () with a class-specific definition.
 *
 * In c++, we have both classes and structs. They are completely interchangeable keywords. The only
 * difference is that, by default, everything in a struct is public and everything in a class is private.
 * When to use structs versus classes is a stylistic decision that depends on the preferences of your
 * development team. I will use the convention that a struct represents a c-like wrapper, where as class
 * represents an object-oriented object in which we would use OOP concepts like polymorphism or inheritance.
 */
struct get_luv_vector
{
	// Another magic number, indicating the size of the vector that we will produce.
	// size_t static const n = 3200u; // may not need this
	
	// number of node?
	u_int n = 1000;

	/**
	 * Generates a random test instance for our Lone Unique Value (LUV) problem.
	 *
	 * An example of overloading the function-call operator.
	 * The const keyword at the end informs the compiler that this function will not
	 * modify any member variables of this struct/class. (Obvious in this case, as the
	 * struct does not contain any non-const member variables.)
	 *
	 * It can be challenging to create meaningful test instances for a given problem.
	 * This function creates a series of pairs, and one unique value.
	 * Here, we need to ensure that the unique value we generate is not randomly also
	 * generated as a pair, or it will no longer be unique.
	 */
	Node  operator() () const
	{
		// Declare the vector that we want to produce and indicate the amount of space it will use.
	
		// Node nn;
		// push one unique random val onto vector
		// or'ing with 1 ensures the value (used as a multiplier below) cannot be zero, by setting
		// the least significant bit
		Node nn;
		for( auto i = 0u; i < n; ++i )
		{
			auto const x = ( std::rand() & ~1u );
			auto const y = ( std::rand() & ~1u );
			std::string name = random_string(4);//giving it a random length of 4
		
			nn.add(x,y,name);

		}


		// std::shuffle( nn.x.begin(), nn.x.end(), std::default_random_engine{} );

		return nn ;
	}
};


/**
 * The function that is run when the application is launched. In this case, runs our benchmarks.
 */
int main()
{
	// Another magic number. *sigh*. Controls the number of test instances for our benchmark.
	// auto const num_test_instances = 100u;
	auto const num_test_instances = 10;

	// For random numbers, one must first seed the random number generator. This is the idiomatic
	// approach for the random number generator libraries that we have chosen.
	std::srand ( static_cast< uint32_t >( std::time(0) ) );

	// Run the sanity-check benchmark.
	mwe_benchmark();

	// Create consistent random data to use with each algorithm/implementation.
	// The {} syntax calls the default constructor for the get_luv_vector struct/class with no arguments.
	auto const random_data = build_rand_vec( get_luv_vector{}
										   , num_test_instances
										   );
	auto const time = timing::benchmark::benchmark( skyline::solution::solve,  random_data );


	std::cout << "Average time per call       = " << time     << " us" << std::endl;

	return 0;
}