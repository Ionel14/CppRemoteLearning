#include <iostream>
#include <cstring>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include "utils/clientUtils.h"
#include "serialization/Message.h"
#include <sstream>

std::string getCurrentDate() {
    boost::gregorian::date today = boost::gregorian::day_clock::local_day();
    std::string dateString = boost::gregorian::to_iso_string(today);
    return dateString;
}

std::string generateRandomName() {
    std::string name = "Client";
    name += std::to_string(rand() % 100);
    return name;
}

int main() {
    int socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFileDescriptor == -1) {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }
    const std::string name = generateRandomName();

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
        std::stringstream ss;
        boost::archive::text_oarchive oa(ss);
        Message msg(userInput, name, getCurrentDate());
        oa << msg;

        std::string serializedMessage = ss.str();
        communicateWithServer(socketFileDescriptor, serializedMessage);
    }

    freeaddrinfo(serverInfo);
    close(socketFileDescriptor);

    return 0;
}

