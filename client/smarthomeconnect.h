#ifndef SMARTHOMECONNECT_H
#define SMARTHOMECONNECT_H

#include <cstring> 
#include <iostream> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h> 
#include <memory>

#include "message.h"

namespace smart_home_client
{

class SmartHomeConnect
{
public:
    SmartHomeConnect();
    void StartConnection();


private:
    std::string RequestString();
    std::string StatusAction();
    std::string AddObject();
    std::string DeleteObject();
    std::string GetAName();
    void sendDataToServer(const std::string& message, int* clientSocket);
    std::stringstream& GetSerializedMessage(const std::string& message);

    std::string username_;
};
    
class SocketDeleter {
public:
    void operator()(int* sockfd) const {
        if (sockfd && *sockfd != -1) {
            close(*sockfd);
            std::cout << "Socket closed" << std::endl;
        }
        delete sockfd;
    }
};

} // namespace smart_home_client
#endif