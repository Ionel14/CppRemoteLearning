#ifndef SMARTHOMECONNECT_H
#define SMARTHOMECONNECT_H

#include <cstring> 
#include <iostream> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h> 
#include <memory>

namespace smart_home_client
{

class SmartHomeConnect
{
public:
    void StartConnection();


private:
    std::string RequestString();
    std::string StatusAction();
    std::string AddObject();
    std::string DeleteObject();
    std::string GetAName();
    void sendDataToServer(const char* message, int* clientSocket);

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