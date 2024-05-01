#ifndef SSH_MANAGE_H
#define SSH_MANAGE_H

#include "serverManage.hpp"
int ssh_connect ( const serverManager& manager );
int scp_connect ( const serverManager& manager );


#endif
