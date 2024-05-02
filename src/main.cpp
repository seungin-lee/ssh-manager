#include <iostream>
#include <string>
#include <vector>
#include "serverManage.hpp"
#include "sshManage.hpp"
#include "common.hpp"

// Initial configuration. Decide the feature of this program.
static std::vector<std::pair<std::string, bool>> features = {
    { "ssh", false },
    { "scp", false }
};

// Initial screen. User should select the feature of this program.
int select_features(){
    static int count = 0;
    int num = 0;
    for (const auto& feature : features) {
        std::cout << num++ << " : " << feature.first << std::endl;
    }
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "Select the target feature : ";
    int index;
    std::cin >> index;
    if ( std::cin.fail() || index > features.size() -1 ){
        cinClear(count);
        return select_features();
    } else {
        features[index].second = true;
        return 0;
    }
}


int main(){
    select_features();
    serverManager manager;
    for (const auto& feature : features){
        if ( feature.second == true ){
            if ( feature.first == "ssh" ) ssh_connect(manager);
            else if ( feature.first == "scp") scp_connect(manager) ;
        }
    }

    return 0;
}

