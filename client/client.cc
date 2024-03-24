#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include "utils/clientUtils.h"

int main() {
    int socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFileDescriptor == -1) {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    struct addrinfo hints{}, *serverInfo;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo("localhost", "8080", &hints, &serverInfo) != 0) {
        std::cerr << "Error getting server address" << std::endl;
        close(socketFileDescriptor);
        return 1;
    }

    if (connect(socketFileDescriptor, serverInfo->ai_addr, serverInfo->ai_addrlen) == -1) {
        std::cerr << "Error connecting to server" << std::endl;
        freeaddrinfo(serverInfo);
        close(socketFileDescriptor);
        return 1;
    }

    std::cout << "Connected to server, waiting for welcome message..." << std::endl;
    std::string welcomeMessage = receiveFromServer(socketFileDescriptor);
    if (!welcomeMessage.empty()) {
        std::cout << "Received from server: " << welcomeMessage << std::endl;
    }

    std::cout << "Enter commands ('exit' to quit):" << std::endl;


    std::string userInput;
    while (true) {
        std::getline(std::cin, userInput);
        if (userInput == "exit") {
            break;
        }
        userInput += '\0';
        communicateWithServer(socketFileDescriptor, userInput);
    }

    freeaddrinfo(serverInfo);
    close(socketFileDescriptor);

    return 0;
}
