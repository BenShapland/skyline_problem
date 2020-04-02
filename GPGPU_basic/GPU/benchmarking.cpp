
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

// #include "xvals.hpp"
// #include "yvals.hpp"
// #include "test-data.hpp"
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



std::vector<std::string> make_names(int number_of_names){
   std::vector<std::string> hold;
   for(int i =0; i<number_of_names; i++){
      hold.push_back(random_string(4));
   }
   return hold;
}

void write_vector_XY_file( const char * filename, std::vector< uint32_t > x , std::vector< uint32_t > y, std::string name, std::vector< std::string > ran_name)
{
	int n = x.size();
    std::ofstream file;
    file.open( filename );
	
	file << "#include \"Node.h\"\n";

    file << "std::vector< XY > "<< name <<" = {";
	for(int i = 0 ; i <x.size()-1;i++){
		file << "{" << x[i] << ", " << y[i] << "}, ";
	}
    file << "{" << x[x.size()-1] << ", " << y[x.size()-1] << "}";
	file << " };";

    file << "\n\n\n";

    // XY xy_array[1]= { XY{5,3} };
    // name-array
    file << "XY " << name <<"_array" <<"[" << n <<"]" <<" = {";
    for(int i = 0 ; i <x.size()-1;i++){
		file << "XY"<<"{" << x[i] << ", " << y[i] << "}, ";
	}
    file << "XY"<< "{" << x[x.size()-1] << ", " << y[x.size()-1] << "}";
    file << " };";
    

    
    file << "\n\n\n";
    // // std::vector< std::string > name = { "ass", "NIPS"};
    // file << "std::vector<  std::string > "<< name <<"_name"<<" = {";
    // for(int i = 0 ; i <x.size()-1;i++){
    //     file << '"' << ran_name[i] <<'"' << ",";
    // }
    // file << '"' << ran_name[x.size()-1] <<'"' ;
    // file << " };";


    // std::vector< std::string > name = { "ass", "NIPS"};
    // file << "std::string "<< name <<"_name"<< "["<<n<<"]" <<" = {";
    // for(int i = 0 ; i <x.size()-1;i++){
    //     file << '"' << ran_name[i] <<'"' << ",";
    // }
    // file << '"' << ran_name[x.size()-1] <<'"' ;
    // file << " };";

    // char char_name[] 
     file << "char char_"<< name <<"[]" <<" = "<<'"';
    for(int i = 0 ; i <x.size()-1;i++){
        file << ran_name[i];
    }
    file  << ran_name[x.size()-1] <<'"'<<";" ;

    file<< std::endl;
    file.close();
}


int main()
{
	// WE MIGHT WANT TO MAKE SURE WHEN WE COPY IT, it does not take extra time to make the Node
	// std::cout<< (xvals[0]) <<"\n";
	// std::cout<< (yvals[1].x) <<"\n";

	//
	int n=10000;//number of random data entrys 
	std::vector< uint32_t > x( n );
    std::generate( std::begin( x ), std::end( x ), [](){ return rand() % 1000; } );
	std::vector< uint32_t > y( n );
    std::generate( std::begin( y ), std::end( y ), [](){ return rand() % 1000; } );

    //random generate strings
    std::vector< std::string > names = make_names(n);
    
	write_vector_XY_file("test-data.hpp", x,y, "data", names);


    // std::cout << data_array[0].x;


    // std::vector< std::string > name = { "ass"}
    // std::out<< name[0]


	return 0;
}


                           

         