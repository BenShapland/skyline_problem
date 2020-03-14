
#include <iostream> // for outputting (printing) to streams (e.g., the terminal)
#include <random> 	// std::rand, std::srand, std::default_random_engine
#include <cmath>	// sqrt()

#include "Node.h"


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



int main(){

    u_int n = 20000;  // Number of data in arrays


	// Node  operator() () const
	// {
	// 	// Declare the vector that we want to produce and indicate the amount of space it will use.
	
	
		// push one unique random val onto vector
		// or'ing with 1 ensures the value (used as a multiplier below) cannot be zero, by setting
		// the least significant bit
		Node nn;
		for( auto i = 0u; i < n; ++i )
		{
			auto const x = ( std::rand() & ~1u );
			auto const y = ( std::rand() & ~1u );
			std::string name = random_string(4);//giving it a random length of 4


			nn.add(x,y,name);  // To add to SoC data struct

		}

		
	


    return 0;
	// }

}