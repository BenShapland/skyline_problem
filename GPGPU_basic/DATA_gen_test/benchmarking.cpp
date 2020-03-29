
#include <iostream> // for outputting (printing) to streams (e.g., the terminal)
#include <random> 	// std::rand, std::srand, std::default_random_engine
#include <cmath>	// sqrt()
#include <cstring>   // std::strcmp()
#include <fstream>   // std::ofstream
#include <stdlib.h>  // srand(), rand()
#include <algorithm> // std::sort(), std::for_each()
#include <vector>
// #include "Node.h"


using std::vector;

#include "xvals.hpp"
// #include "yvals.hpp"
#include "test-test.hpp"

void write_to_file( const char * filename, std::vector< uint32_t > x , std::vector< uint32_t > y, std::string name )
{


    std::ofstream file;
    file.open( filename );
	
	
	file << "#include \"Node.h\"\n";

    file << "std::vector< XY > "<< name <<" = {";

	for(int i = 0 ; i <x.size()-1;i++){
		file << "{" << x[i] << ", " << y[i] << "}, ";
	}

    file << "{" << x[x.size()-1] << ", " << y[x.size()-1] << "}";
	// std::for_each( data.begin(), data.end() - 1, [ &file ]( auto const val ){ file << val << ", "; } );
    
	
	
	file << " };" << std::endl;

    file.close();
}


int main()
{
	//WE MIGHT WANT TO MAKE SURE WHEN WE COPY IT, it does not take extra time to make the Node
	// std::cout<< (xvals[0]) <<"\n";
	// std::cout<< (yvals[1].x) <<"\n";


	int n=10;//number of random data entrys 
	std::vector< uint32_t > x( n );
    std::generate( std::begin( x ), std::end( x ), [](){ return rand() % 1000; } );

	std::vector< uint32_t > y( n );
    std::generate( std::begin( y ), std::end( y ), [](){ return rand() % 1000; } );
	
	write_to_file("test-data.hpp", x,y, "yvals.hpp" );

	return 0;
}


                           

         