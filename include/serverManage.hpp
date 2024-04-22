#ifndef SERVER_MANAGE_H
#define SERVER_MANAGE_H

#include <string>
#include <vector>

typedef struct serverInfo {
    std::string ip; // ip address
    std::string target; // username@ipaddress
    std::string alias; // alias
} serverInfo;

typedef struct serverConfig {
    std::string username; // username
    std::vector<serverInfo> servers;
} serverConfig;

class serverManager {
    private:
        // serverManager could detect multiple config file 
        std::vector<std::string> configFile;
        // serverManager could manage multiple serverConfig.
        std::vector<serverConfig> serverConfigList; 
    public:
        serverManager(){
            loadConfigs(detectConfigFiles());
        }
        // detect the cofig file and return the specific file
        std::string detectConfigFiles(); 
        // load, parse and fill the object(serverConfig, serverConfigList)
        void loadConfigs(const std::string& filePath); 
        // print the config file list
        void printConfigFiles() const; 
        // print the serverConfigList
        void printConfigs() const; 
        // return the target
        std::string returnTargetAddress (const int idx) const; 
};

#endif

