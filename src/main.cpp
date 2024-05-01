#include "serverManage.hpp"
#include "sshManage.hpp"
#include <iostream>
#include <string>
#include <vector>

// Initial configuration. Decide the feature of this program.
static std::vector<std::pair<std::string, bool>> features = {
    { "ssh", false },
    { "scp", false }
};

// Initial screen. User should select the feature of this program.
void select_features(){
    int num = 0;
    for (const auto& feature : features) {
        std::cout << num++ << " : " << feature.first << std::endl;
    }
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "Select the target feature : ";
    int index;
    std::cin >> index;

    features[index].second = true;

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

