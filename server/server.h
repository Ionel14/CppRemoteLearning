#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <stdexcept>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include "smarthome.h"
#include "myuniqueptr.h"
#include "devices/device.h"
#include "sensors/sensor.h"
#include "colleagueuniqueptr.h"
#include "message.h"
#include "threadpool.h"

namespace smartHome {
    class Server {
    public:
        Server(size_t num_threads);
        ~Server();

        void start();

    private:
        struct SocketDeleter {
            void operator()(int* socket) const {
                close(*socket);
                delete socket;
            }
        };

        static std::vector<std::string> split(const std::string& input, const std::string& delimiter);
        static void sendDataToClient(const char *message, int *clientSocket);
        static bool getReqFromClient(int *clientSocket, SmartHome& home);
        static void processClientRequest(MyUniquePtr<int, SocketDeleter>& clientSocket, SmartHome& home);

        MyUniquePtr<int, SocketDeleter> server_fd;
        sockaddr_in serverAddress;
        MyThreadPool threadpool;

        std::mutex socketMutex; 
        std::mutex homeMutex;
    };
}

#endif // SERVER_H