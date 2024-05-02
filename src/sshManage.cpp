#include <cstdlib> // system command
#include <iostream>
#include "sshManage.hpp"
#include "common.hpp"

static int send_command(std::string& command){
    std::cout << command << std::endl;

    int result = system(command.c_str()); //system should receive 'const char*' argument
    if (result != 0) {
        std::cerr << "Failed to execute command: " << command << std::endl;
        return -1;
    } else return 0;
}

int ssh_connect( const serverManager& manager){
    static int count = 0;
    int num = manager.printConfigs();
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "Select the target server : ";

    int index;
    std::cin >> index;
    if ( std::cin.fail() || index > num -1){ 
        cinClear(count);
        return ssh_connect( manager );
    }
        
    std::string target;
    target = manager.returnTargetAddress(index);

    std::cout << "Trying to connect to " << target << std::endl;
    std::string command = "ssh -X " + target;
    send_command(command);

    return 0;
}

void enter_path(std::string& localPath, std::string& remotePath, std::string& username){
    std::cout << "Enter the absolute path of local file/directory path\n" << "Local Path : " ;
    std::cin >> localPath;
    const char* localUserName = getenv("USER");
    if ( !localUserName ) {
        std::cout << "\nEnvironment Variable 'USER' is not set in this system.\n" ;
        std::cout << "Please note to use '~' path.\n";
    } else {
        if ( localPath.find("~") != std::string::npos){
            std::string localuname(localUserName);
            localPath.replace(localPath.find("~"), 1, "/home/"+ localuname);
        }
    }
    std::cout << "\nLocal path is set as " << localPath <<std::endl;

    std::cout << "\nEnter the absolute path of remote file/directory path\n" << "Remote Path : " ;
    std::cin >> remotePath;
    if ( remotePath.find("~") != std::string::npos ){
        remotePath.replace(remotePath.find("~"), 1, "/home/"+username);
    }
    std::cout << "\nRemote path is set as " << remotePath <<std::endl;
    std::cout << std::endl;
}

int scp_connect( const serverManager& manager){
    static int count = 0;
    int num = manager.printConfigs();
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "Select the target server : ";

    int index;
    std::cin >> index;
    if ( std::cin.fail() || index > num -1){
        cinClear(count);
        return scp_connect( manager );
    }

    std::string target;
    std::string username;

    target = manager.returnTargetAddress(index);
    username = manager.returnTargetUsername(index);

    count = 0;
    std::cout << "\nSCP Target is " << target << std::endl;
    std::cout << "0 : Send to the target" << std::endl;
    std::cout << "1 : Receive from the target" << std::endl;
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "Select the Send/Receive operation : ";
    std::cin >> index;
    while (std::cin.fail() || index > 1){
        cinClear(count);
        std::cout << "\nSCP Target is " << target << std::endl;
        std::cout << "0 : Send to the target" << std::endl;
        std::cout << "1 : Receive from the target" << std::endl;
        std::cout << "------------------------------------------------" << std::endl;
        std::cout << "Select the Send/Receive operation : ";
        std::cin >> index;
    }

    std::string localPath;
    std::string remotePath;
    std::string command;
    if ( index == 0 ) { // Send to the target
        std::cout << "\n...SEND OPERATION..." << std::endl;
        enter_path(localPath, remotePath, username);
        command = "scp -r " + localPath + " " + target + ":" + remotePath;
        std::cout << "Trying to connect to " << target << std::endl;
    } else if ( index == 1 ) { // Receive from the target
        std::cout << "\n...RECEIVE OPERATION..." << std::endl;
        enter_path(localPath, remotePath, username);
        command = "scp -r "+ target + ":" + remotePath + " " + localPath;
        std::cout << "Trying to connect to " << target << std::endl;
    }

    return send_command( command );
}
