#include <cstdlib> // system command
#include <iostream>
#include "sshManage.hpp"


int ssh_connect( const serverManager& manager){
    manager.printConfigs();
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "Select the target server : ";

    int index;
    std::cin >> index;

    try {
        std::string target = manager.returnTargetAddress(index);
        std::cout << "Trying to connect to " << target << std::endl;
        std::string command = "ssh -X " + target;
        std::cout << command << std::endl;
    
        int result = system(command.c_str()); //system should receive 'const char*' argument
        if (result != 0) {
            std::cerr << "Failed to execute command: " << command << std::endl;
            return -1;
        }

    } catch (const std::out_of_range& e){
        std::cerr << "Error : " << e.what() << std::endl;
        return -1;
    }

    return 0;
}




