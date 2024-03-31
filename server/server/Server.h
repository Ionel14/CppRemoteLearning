#ifndef NAGARROREMOTELEARNINGSERVER_SERVER_H
#define NAGARROREMOTELEARNINGSERVER_SERVER_H


#include <netinet/in.h>

namespace smart_home {

    class Server {
    public:
        Server();
        ~Server();
        bool initializeSocket();
        void run();

    private:
        int socketFileDescriptor;
        sockaddr_in serverAddress{};
    };

}


#endif
