#include "Server.h"
#include "ClientHandler.h"
#include <unistd.h>
#include <iostream>
#include <thread>

namespace smart_home {

    Server::Server() : socketFileDescriptor(-1) {}

    Server::~Server() {
        if (socketFileDescriptor != -1) {
            close(socketFileDescriptor);
        }
    }

    bool Server::initializeSocket() {
        socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
        if (socketFileDescriptor == -1) {
            return false;
        }

        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = INADDR_ANY;
        serverAddress.sin_port = htons(8080);

        if (bind(socketFileDescriptor, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1) {
            return false;
        }

        if (listen(socketFileDescriptor, 5) == -1) {
            return false;
        }

        return true;
    }

    void Server::run() {
        std::cout << "Server listening on port 8080..." << std::endl;

        while (true) {
            sockaddr_in clientAddress{};
            socklen_t clientAddressLength = sizeof(clientAddress);
            int clientSocketFileDescriptor = accept(socketFileDescriptor, (struct sockaddr *) &clientAddress, &clientAddressLength);
            if (clientSocketFileDescriptor == -1) {
                std::cerr << "Error accepting connection" << std::endl;
                continue;
            }

            std::thread(ClientHandler::handleClient, clientSocketFileDescriptor).detach();
        }
    }

}