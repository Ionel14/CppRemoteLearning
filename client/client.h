#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include "message.h"

namespace smartHome{
    class Client {
    public:
        Client();
        ~Client();

        void run();

    private:
        int clientSocket;
    };
}


#endif // CLIENT_H