#include <iostream>
#include <string>
#include <vector>

#include <sstream>
#include <fstream>
#include <algorithm>

#include "serverManage.hpp"
#include <dirent.h>

#define CONF_DIR_NAME   ".ssh-manager.conf"

std::string serverManager::detectConfigFiles(){
    if (!configFile.empty()) configFile.clear();
    const char* homePath = std::getenv("HOME");
    if (!homePath){
        std::cerr << "Home directory path cannot be determined.\n";
        std::exit(EXIT_FAILURE);
    }
    std::string confDirPath = std::string(homePath) + "/" + CONF_DIR_NAME;
    DIR * dir;
    struct dirent *ent;
    dir = opendir(confDirPath.c_str());
    if( dir!= NULL){
        while ((ent=readdir(dir)) != NULL){
            if ( ent->d_name == std::string(".") || ent->d_name == std::string("..") ) continue; // except . and ..
            configFile.push_back(confDirPath + "/" + std::string(ent->d_name));
        }
        closedir(dir);
    } else {
        std::cerr << "can't open the dir\n";
        std::exit(EXIT_FAILURE);
    }
    serverManager::printConfigFiles();
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "Select the target config file : ";

    int index;
    std::cin >> index;
    if ( index >= configFile.size()) {
        std::cerr << "Error : Out of Index. " << "Select the right index again\n\n";
        return detectConfigFiles(); // recursive
    } else return configFile[index];
}

void serverManager::loadConfigs(const std::string& filePath){
    std::ifstream file(filePath);
    std::string line;
    serverConfig currentConfig;
    bool isConfigActive = false;

    if (!file.is_open()){
        std::cerr << "Cannot open the config file.\n";
        std::cerr << "Check the '.connect.easy.conf' dir or specify the config file.\n";
        std::cerr << "Exit..\n";
        std::exit(EXIT_FAILURE);
        return;
    }
    // read file line by line then parse username and ip address
    // Example of config file
    // ------------------------
    // username: travis
    // ip: ['192.168.45.131','192.168.45.132'] 
    //
    // username: seungin
    // ip: ['100.1.4.2']
    // ------------------------

    while (std::getline(file, line)){
        std::istringstream iss(line);
        std::string key; 
        std::string value;
        if (std::getline(iss, key, ':')){ // get the value before the ':' keyword
            std::getline(iss, value); // get the value after the ':' keyword 

            if (key=="username") {
                // if it faces the second 'username'contents, serverConfig struct must be generated again.
                if (isConfigActive) {
                    serverConfigList.push_back(currentConfig);
                    currentConfig = serverConfig();
                }
                value.erase(std::remove(value.begin(), value.end(), ' '), value.end()); //remove blank
                value.erase(std::remove(value.begin(), value.end(), '\t'), value.end()); //remove tab
                currentConfig.username = value;
                isConfigActive = true;
            } else if ( key == "ip" && isConfigActive){
                // remove blank and [] then sperate with ','
                value.erase(std::remove(value.begin(), value.end(), '['), value.end());
                value.erase(std::remove(value.begin(), value.end(), ']'), value.end());
                value.erase(std::remove(value.begin(), value.end(), ' '), value.end());
                std::istringstream valueStream(value);
                std::string ip;
                while(std::getline(valueStream, ip, ',')){
                    ip = ip.substr(1,ip.length()-2);
                    currentConfig.iplist.push_back(ip);
                    currentConfig.target.push_back(currentConfig.username + "@" + ip);
                }
            }
        }
    }

    if (isConfigActive) {
        serverConfigList.push_back(currentConfig);
    }
}

void serverManager::printConfigFiles() const{
    std::cout << std::endl;
    int i = 0;
    for (const auto& filename : configFile){
        std::cout << i++ << " : " << filename << std::endl;
    }
}
void serverManager::printConfigs() const{
    std::cout << std::endl;
    int i = 0;
    for (const auto& config : serverConfigList){
        for (const auto& target : config.target){
            std::cout << i++ << " : " << target << std::endl;
        }
    }
}

std::string serverManager::returnTargetAddress (const int idx) const {
    int count = 0;
    for (const auto& config : serverConfigList){
        for (const auto& target : config.target){
            if(count == idx) {
                return target;
            }
            count++;
        }
    }

    throw std::out_of_range("Index out of range");
}

