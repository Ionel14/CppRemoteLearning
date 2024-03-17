#include "client.h"

namespace smartHome{
    Client::Client() : clientSocket(-1) {}

    Client::~Client() {
        if (clientSocket != -1) {
            close(clientSocket);
        }
    }

    void Client::run() {
        // Create a socket
        clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (clientSocket == -1) {
            std::cerr << "Error: Failed to create socket\n";
            return;
        }

        // Specify the details of the server we are connecting to
        sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(8080);
        serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

        // Connect to server
        if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
            std::cerr << "Error: Connection failed\n";
            return;
        }

        // Sending requests to the server
        while (true) {
            // Print menu
            std::cout << "1. Status-house\n";
            std::cout << "2. Status-room\n";
            std::cout << "3. Status-device\n";
            std::cout << "4. Status-sensor\n";
            std::cout << "5. Add-device\n";
            std::cout << "6. Add-sensor\n";
            std::cout << "7. Delete-device\n";
            std::cout << "8. Delete-sensor\n";

            // Get request
            std::string request;
            std::cout << "Enter request: ";
            std::getline(std::cin, request);

            if (request == "Status-room" || request == "Status-device" || request == "Status-sensor") {
                std::string id;
                std::cout << "Enter id: ";
                std::getline(std::cin, id);
                request += "-" + id;
            }

            // Send request
            int bytesSent = send(clientSocket, request.c_str(), request.length(), 0);
            if (bytesSent == -1) {
                std::cerr << "Error: Failed to send request\n";
                break;
            }

            // Wait for server response
            char buffer[1024] = {0};
            int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
            if (bytesReceived == -1) {
                std::cerr << "Error: Failed to receive response\n";
                break;
            }

            std::cout << "Server response: " << buffer << std::endl;

            if (request == "quit") {
                std::cout << "Exiting...\n";
                break;
            }
        }
    }

}
