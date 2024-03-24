#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sstream>
#include "user/User.h"
#include "utils/serverUtils.h"

int main() {
    smart_home::User &user = smart_home::User::getInstance();

    int socketFileDescriptor;
    if ((socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8080);

    if (bind(socketFileDescriptor, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Error binding socket" << std::endl;
        close(socketFileDescriptor);
        return 1;
    }

    if (listen(socketFileDescriptor, 5) == -1) {
        std::cerr << "Error listening for connections" << std::endl;
        close(socketFileDescriptor);
        return 1;
    }

    while (true) {
        std::cout << "Server listening on port 8080..." << std::endl;

        sockaddr_in clientAddress{};
        socklen_t clientAddressLength = sizeof(clientAddress);
        int clientSocketFileDescriptor;

        if ((clientSocketFileDescriptor = accept(socketFileDescriptor, (struct sockaddr *) &clientAddress,
                                                 &clientAddressLength)) == -1) {
            std::cerr << "Error accepting connection" << std::endl;
            continue;
        }

        std::cout << "Connection established with client" << std::endl;
        send(clientSocketFileDescriptor, welcomeMessage, strlen(welcomeMessage), 0);

        while (true) {
            char buffer[1024] = {0};
            int bytesRead = recv(clientSocketFileDescriptor, buffer, sizeof(buffer), 0);

            if (bytesRead <= 0) {
                if (bytesRead == 0) {
                    std::cout << "Client disconnected" << std::endl;
                    close(clientSocketFileDescriptor);
                } else {
                    std::cerr << "Error receiving data" << std::endl;
                }
                break;
            }

            buffer[bytesRead] = '\0';
            std::cout << "Received from client: " << buffer << std::endl;

            std::string request(buffer);
            if (request == "exit") {
                std::cout << "Client requested to close the connection" << std::endl;
                break;
            }


            RequestType requestType = determineRequestType(request);

            // For device requests
            int deviceType = -1;

            // For sensor requests
            RoomType roomType = RoomType::UNKNOWN_ROOM;
            std::string sensorName;
            std::vector<std::string> tokens;
            std::stringstream ss(request);
            std::string token;

            // For response
            std::string status;

            if (isDeviceRequest(requestType)) {
                deviceType = std::stoi(request.substr(request.find(",") + 1));
            } else if (isSensorRequest(requestType)) {
                while (getline(ss, token, ',')) {
                    tokens.push_back(token);
                }

                if (tokens.size() > 1) {
                    roomType = getRoomTypeFromInt(std::stoi(tokens[1]));
                }

                if (tokens.size() > 2) {
                    sensorName = tokens[2] + "_" + std::to_string(roomType);
                }
            } else {
                send(clientSocketFileDescriptor, "Invalid request.", 16, 0);
                continue;
            }

            switch (requestType) {
                case RequestType::GetDevicesStatus:
                    status = user.getDevicesStatus();
                    send(clientSocketFileDescriptor, status.c_str(), status.length(), 0);
                    break;
                case RequestType::AddDevice:
                    try{
                        user.addDevice(static_cast<DeviceType>(deviceType));
                        send(clientSocketFileDescriptor, "Device added.", 13, 0);
                    } catch (std::exception& e){
                        send(clientSocketFileDescriptor, e.what(), strlen(e.what()), 0);
                    }
                    break;
                case RequestType::RemoveDevice:
                    try {
                        user.removeDevice(static_cast<DeviceType>(deviceType));
                        send(clientSocketFileDescriptor, "Device removed.", 15, 0);
                    } catch (std::exception& e){
                        send(clientSocketFileDescriptor, e.what(), strlen(e.what()), 0);
                    }
                    break;
                case RequestType::GetDeviceStatus:
                    try {
                        status = user.getDeviceStatus(static_cast<DeviceType>(deviceType));
                        send(clientSocketFileDescriptor, status.c_str(), status.length(), 0);
                    } catch (std::exception& e){
                        send(clientSocketFileDescriptor, e.what(), strlen(e.what()), 0);
                    }
                    break;
                case RequestType::GetHouseSensorStatus:
                    status = user.getHouseSensorStatus();
                    send(clientSocketFileDescriptor, status.c_str(), status.length(), 0);
                    break;
                case RequestType::GetRoomSensorStatus:
                    if (tokens.size() < 2) {
                        std::cout << "Invalid parameters for GetRoomSensorStatus." << std::endl;
                        send(clientSocketFileDescriptor, "Invalid parameters for GetRoomSensorStatus.", 38, 0);
                    } else {
                        status = user.getRoomSensorStatus(roomType);
                        send(clientSocketFileDescriptor, status.c_str(), status.length(), 0);
                    }
                    break;
                case RequestType::GetSensorStatus:
                    if (tokens.size() < 3) {
                        send(clientSocketFileDescriptor, "Invalid parameters for GetSensorStatus.", 38, 0);
                    } else {
                        status = user.getSensorStatus(roomType, sensorName);
                        send(clientSocketFileDescriptor, status.c_str(), status.length(), 0);
                    }
                    break;
                case RequestType::AddSensorToRoom:
                    if (tokens.size() < 3) {
                        send(clientSocketFileDescriptor, "Invalid parameters for AddSensorToRoom.", 37, 0);
                    } else {
                        user.addSensorToRoom(roomType, sensorName);
                        send(clientSocketFileDescriptor, "Sensor added to room.", 21, 0);
                    }
                    break;
                case RequestType::RemoveSensorFromRoom:
                    if (tokens.size() < 3) {
                        send(clientSocketFileDescriptor, "Invalid parameters for RemoveSensorFromRoom.", 40, 0);
                    } else {
                        user.removeSensorFromRoom(roomType, sensorName);
                        send(clientSocketFileDescriptor, "Sensor removed from room.", 25, 0);
                    }
                    break;
                default:
                    send(clientSocketFileDescriptor, "Invalid request.", 16, 0);
                    break;
            }
        }
    }
}