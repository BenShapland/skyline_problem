
#include <iostream> // for outputting (printing) to streams (e.g., the terminal)
#include <random> 	// std::rand, std::srand, std::default_random_engine
#include <cmath>	// sqrt()
#include <cstring>   // std::strcmp()
#include <fstream>   // std::ofstream
#include <stdlib.h>  // srand(), rand()
#include <algorithm> // std::sort(), std::for_each()
#include <vector>
#include <sstream>
// #include "Node.h"


using std::vector;

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

    file << "XY " << name <<"_array" <<"[" << n <<"]" <<" = {";
    for(int i = 0 ; i <x.size()-1;i++){
		file << "XY"<<"{" << x[i] << ", " << y[i] << "}, ";
	}
    file << "XY"<< "{" << x[x.size()-1] << ", " << y[x.size()-1] << "}";
    file << " };";
    

    
    file << "\n\n\n";
    file << "std::vector<  std::string > "<< name <<"_name"<<" = {";
    for(int i = 0 ; i <x.size()-1;i++){
        file << '"' << ran_name[i] <<'"' << ",";
    }
    file << '"' << ran_name[x.size()-1] <<'"' ;
    file << " };";

    file << "\n\n\n";

     file << "char char_"<< name <<"[]" <<" = "<<'"';
    for(int i = 0 ; i <x.size()-1;i++){
        file << ran_name[i];
    }
    file  << ran_name[x.size()-1] <<'"'<<";" ;

    file<< std::endl;
    file.close();
}


int main(int argc, char** argv)
{


    if(argc !=2){
        std::cout<<"Missing Argument: num_data_points\n";
        return 0;
    }
    std::istringstream iss( argv[1] );
    int n =0;
    if (iss >> n)
    {
	  std::cout<<"Successfully Generated File\n";
    }
    else{
        std::cout<<"Error\n";
        return 0;
    }

	std::vector< uint32_t > x( n );
    std::generate( std::begin( x ), std::end( x ), [](){ return rand() % 1000; } );
	std::vector< uint32_t > y( n );
    std::generate( std::begin( y ), std::end( y ), [](){ return rand() % 1000; } );

    //random generate strings
    std::vector< std::string > names = make_names(n);
    
	write_vector_XY_file("test-data.hpp", x,y, "data", names);




	return 0;
}


                           

         