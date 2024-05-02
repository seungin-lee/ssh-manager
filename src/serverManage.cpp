#include <iostream>
#include <string>
#include <vector>

#include <sstream>
#include <fstream>

#include "serverManage.hpp"
#include "json.hpp"
#include <dirent.h>
#include "common.hpp"

#define CONF_DIR_NAME   ".ssh-manager"
#define CONF_FILE_PATTERN ".conf"

using json = nlohmann::json;

std::string serverManager::detectConfigFiles(){
    static int count = 0;
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
            std::string d_name = std::string(ent->d_name);
            if ( d_name == std::string(".") || d_name == std::string("..") ) continue; // except . and ..
            if ( d_name.find(CONF_FILE_PATTERN) != std::string::npos ) {
                configFile.push_back(confDirPath + "/" + std::string(ent->d_name));
            }
        }
        closedir(dir);
    } else {
        std::cerr << "can't open the dir\n";
        std::exit(EXIT_FAILURE);
    }

    if ( configFile.size() > 1 ){
        serverManager::printConfigFiles();
        std::cout << "------------------------------------------------" << std::endl;
        std::cout << "Select the target config file : ";
    
        int index;
        std::cin >> index;
        if ( std::cin.fail() || index > configFile.size() -1 ) {
            cinClear( count );
            return detectConfigFiles(); // recursive
        } else 
            return configFile[index];
    } else if ( configFile.size() == 1 ){
        std::cout << configFile[0] << " is selected.\n";
        return configFile[0];
    } else {
        std::cout << "There is no config file. Please make it. Refer the directory .ssh-manager\n";
        std::cout << "Config file must contain '.conf'\n";
        std::exit(EXIT_FAILURE);
    }

}

void serverManager::loadConfigs(const std::string& filePath){
    std::ifstream file(filePath);
    serverInfo currentInfo;
    serverConfig currentConfig;
    bool isConfigActive = false;

    if (!file.is_open()){
        std::cerr << "Cannot open the config file.\n";
        std::cerr << "Check the '.ssh-manager.conf' dir or specify the config file.\n";
        std::cerr << "Exit..\n";
        std::exit(EXIT_FAILURE);
        return;
    }

    try {
        json jfile;
        file >> jfile;
    
        for (auto& element : jfile){
            // if it faces the second 'username'contents, serverConfig struct must be generated again.
            if ( isConfigActive) {
                this->serverConfigList.push_back(currentConfig);
                currentConfig = serverConfig(); //error point
            }
            currentConfig.username = element["username"];
            isConfigActive = true;
            for ( auto& ipInfo : element["ip"] ){
                currentInfo.username = currentConfig.username;
                currentInfo.ip = ipInfo["address"];
                currentInfo.target = currentConfig.username + "@" + currentInfo.ip;
                currentInfo.alias = ipInfo["alias"];
                currentConfig.servers.push_back(currentInfo);
                currentInfo = serverInfo();
            }
        }
    
        if (isConfigActive) {
            serverConfigList.push_back(currentConfig);
        }
    } catch ( json::parse_error& e) {
        std::cout << "parsing error: " << e.what() << '\n';
        std::exit(EXIT_FAILURE);
    } catch ( json::exception& e) {
        std::cout << "Exception: " << e.what() << '\n';
        std::exit(EXIT_FAILURE);
    }

}

void serverManager::printConfigFiles() const{
    std::cout << std::endl;
    int i = 0;
    for (const auto& filename : configFile){
        std::cout << i++ << " : " << filename << std::endl;
    }
}
int serverManager::printConfigs() const{
    int num = 0;
    std::cout << std::endl;
    for (const auto& config : serverConfigList){
        for ( int j = 0; j < config.servers.size(); j++){
            std::cout << num++ << " : " << config.servers[j].target << " (" << config.servers[j].alias << ")" << std::endl;
        }
    }
    return num-1;
}

std::string serverManager::returnTargetAddress (const int idx) const {
    int count = 0;
    for (const auto& config : serverConfigList){
        for ( int j = 0; j < config.servers.size(); j++){
            if(count == idx) {
                return config.servers[j].target;
            }
            count++;
        }
    }
    return ""; // idx is sure in the range. So it is not necessary to add exception
}

std::string serverManager::returnTargetUsername (const int idx) const {
    int count = 0;
    for (const auto& config : serverConfigList){
        for ( int j = 0; j < config.servers.size(); j++){
            if(count == idx) {
                return config.servers[j].username;
            }
            count++;
        }
    }
    return "";
}
