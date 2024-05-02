#include "common.hpp"
#include <iostream>
#include <limits>


void cinClear( int& count ){
    std::cin.clear();   // clear the stream error status
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear buffer
    std::cerr << "\033[31mError : Out of Index. " << "Select the right index again\033[0m\n\n";
    count++;
    if ( count == 5 ) {
        std::cerr << "\nProgram terminate." << std::endl;
        std::exit(EXIT_FAILURE);
    }
}
