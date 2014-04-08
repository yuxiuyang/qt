#include "netdev.h"
#include <unistd.h>
NetDev::NetDev()
{
    m_sockFd = -1;
}
NetDev::~NetDev()
{
    if(m_sockFd!=-1){
        close(m_sockFd);
    }
}
