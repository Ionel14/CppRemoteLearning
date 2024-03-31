#include "ClientHandler.h"
#include "../utils/serverUtils.h"
#include "../serialization/Message.h"
#include <boost/archive/text_iarchive.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <string>
#include <sys/socket.h>

namespace smart_home {
    void ClientHandler::handleClient(int clientSocketFileDescriptor) {
        std::ofstream logFile("../logs/requests_log.txt", std::ios::app);

        smart_home::User &user = smart_home::User::getInstance();
        std::cout << "Connection established with client" << std::endl;
        send(clientSocketFileDescriptor, welcomeMessage, strlen(welcomeMessage), 0);

        while (true) {
            char buffer[1024] = {0};
            int bytesRead = recv(clientSocketFileDescriptor, buffer, sizeof(buffer), 0);

            std::stringstream ss;
            ss.write(buffer, bytesRead);

            if (bytesRead <= 0) {
                if (bytesRead == 0) {
                    std::cout << "Client disconnected" << std::endl;

                } else {
                    std::cerr << "Error receiving data" << std::endl;
                }
                break;
            }

            try {
                boost::archive::text_iarchive ia(ss);
                Message msg;
                ia >> msg;
                std::cout << "Received message from " << msg.sender << " saying: " << msg.text << std::endl;

                logFile << "DATE: " << msg.date << " Received message from " << msg.sender << " saying: " << msg.text << std::endl;

                std::string request(msg.text);
                if (request == "exit") {
                    std::cout << "Client " << msg.sender <<  " requested to close the connection" << std::endl;
                    break;
                }

                std::string response;
                std::vector<std::string> tokens = splitString(request, ',');
                RequestType requestType = determineRequestType(request);

                if (isDeviceRequest(requestType)) {
                    response = handleDeviceRequest(user, requestType, request);
                } else if (isSensorRequest(requestType)) {
                    response = handleSensorRequest(user, requestType, tokens);
                } else {
                    response = "Invalid request.";
                }

                send(clientSocketFileDescriptor, response.c_str(), response.length(), 0);
            } catch (const boost::archive::archive_exception& e) {
                std::cerr << "Error deserializing message: " << e.what() << std::endl;
            }
        }
        close(clientSocketFileDescriptor);

        logFile.close();
    }
}