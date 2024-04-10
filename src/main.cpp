#include "serverManage.hpp"
#include "sshManage.hpp"

int main(){
    serverManager manager;
    ssh_connect( manager );
    return 0;
}

