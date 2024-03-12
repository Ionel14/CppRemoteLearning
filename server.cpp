#include "headers/smart_home.h"
#include "headers/smart_home_manager.h"
#include "headers/unique_ptr_colleague.h"

#include <charconv>
#include <cstring> 
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h> 
#include <unistd.h>
#include <vector>

using namespace smarthome;


void error(const char *msg) {
    std::cerr << msg;
    exit(1);
}

auto& writeRooms(SmartHome& smartHome, int newsockfd) {
    std::string message;
    auto& rooms = smartHome.getRooms();
    for (int i = 0; i < rooms.size(); i++) {
        message += std::to_string(i + 1) + ". " + rooms[i]->getName() + "\n";
    }
    if (write(newsockfd, message.c_str(), message.size()) < 0) {
        error("Error writing to socket");
    }
    return rooms;
}

int readIndex(int newsockfd, char buffer[]) {
    bzero(buffer, 512);
    if (read(newsockfd, buffer, 512) < 0) {
        error("Error reading from socket");
    }
    return strtol(buffer, nullptr, 10) - 1;
}

auto& writeDevices(UniquePointer<Room>& room, int newsockfd) {
    std::string message;
    auto& devices = room->getDevices();
    for (int i = 0; i < devices.size(); i++) {
        message += std::to_string(i + 1) + ". " + devices[i]->getName() + "\n";
    }
    if (write(newsockfd, message.c_str(), message.size()) < 0) {
        error("Error writing to socket");
    }
    return devices;
}

auto& writeSensor(UniquePointer<Device>& device, int newsockfd) {
    std::string message;
    auto& sensors = device->getSensors();
    for (int i = 0; i < sensors.size(); i++) {
        message += std::to_string(i + 1) + ". " + sensors[i]->getName() + "\n";
    }
    if (write(newsockfd, message.c_str(), message.size()) < 0) {
        error("Error writing to socket");
    }
    return sensors;
}

void readNewData(int newsockfd, char buffer[], bool sendWrite = true) {
    bzero(buffer, 512);
    if (read(newsockfd, buffer, 512) < 0) {
        error("Error reading from socket");
    }
    if (sendWrite) {
        if (write(newsockfd, " ",  1) < 0) {
            error("Error writing to socket"); 
        }
    }         
}

int main(int argc, char *argv[]) {
    SmartHome smartHome;
    try {
        smartHome = SmartHomeManager::readDataFromFile("test_client_server.txt");
    } catch (std::exception& e) {
        std::cerr << e.what();
    }

    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[512], buffer2[512];
    std::string message;
    int i1, i2;
    struct sockaddr_in serv_addr, cli_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) error("Error opening socket");

    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = argc == 2 ? atoi(argv[1]) : 3000;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
        error("Error on binding");
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0) error("Error on accept");

    // Read first input
    readNewData(newsockfd, buffer, false);

    while (strcmp(buffer, "0") != 0) {
        // GET STATUS
        if (strcmp(buffer, "status room") == 0 || strcmp(buffer, "status device") == 0 || strcmp(buffer, "status sensor") == 0) {
            // Write rooms
            auto& rooms = writeRooms(smartHome, newsockfd);

            // Read room index
            i1 = readIndex(newsockfd, buffer2);

            if (strcmp(buffer, "status sensor") == 0 || strcmp(buffer, "status device") == 0) {
                // Write devices from room
                auto& devices = writeDevices(rooms[i1], newsockfd);

                // Read device index
                i1 = readIndex(newsockfd, buffer2);

                if (strcmp(buffer, "status sensor") == 0) {
                    // Write sensor from device
                    auto& sensors = writeSensor(devices[i1], newsockfd);

                    // Read sensor index
                    i1 = readIndex(newsockfd, buffer2);

                    // Write status sensors
                    auto& sensor = sensors[i1];
                    std::string message = sensor->getName() + ": " + std::to_string(sensor->getValue()) + "\n";
                    if (write(newsockfd, message.c_str(), message.size()) < 0) error("Error writing to socket");
                } else {
                    // Write status device
                    auto& device = devices[i1];
                    std::string message = device->getName() + ": " + (device->getState() == true ? "on" : "off") + "\n";
                    if (write(newsockfd, message.c_str(), message.size()) < 0) error("Error writing to socket");
                }
            } else {
                // Write status room
                std::string message = SmartHomeManager::getStatusRoom(smartHome, i1);
                if (write(newsockfd, message.c_str(), message.size()) < 0) error("Error writing to socket");
            }
        } else if (strcmp(buffer, "status home") == 0) { 
            // Write status home
            message = SmartHomeManager::getStatusHome(smartHome);
            if (write(newsockfd, message.c_str(), message.size()) < 0) error("Error writing to socket");
        } else if (strcmp(buffer, "add device") == 0 || strcmp(buffer, "add sensor") == 0) { 
        // ADD NEW ENTITY
            std::string name;
            int type, value;
            bool state;
            
            // Write rooms
            auto& rooms = writeRooms(smartHome, newsockfd);

            // Read room index
            i1 = readIndex(newsockfd, buffer2);

            if (strcmp(buffer, "add sensor") == 0) {
                // Write devices from room
                auto& devices = writeDevices(rooms[i1], newsockfd);
                
                // Read device index
                i2 = readIndex(newsockfd, buffer2);
                bzero(buffer2, 512);

                // Write sensor types
                message = "1. Humidity\n2. Light\n3. Temperature\n\n";
                if (write(newsockfd, message.c_str(), message.size()) < 0) error("Error writing to socket");

                // Read sensor type
                readNewData(newsockfd, buffer2);
                type = strtol(buffer2, nullptr, 10);

                // Read sensor name
                readNewData(newsockfd, buffer2);
                name = buffer2;

                // Read sensor value
                readNewData(newsockfd, buffer2, false);
                value = strtol(buffer2, nullptr, 10);

                // Add new sensor
                UniquePointer<Sensor> sensor;
                switch (type) {
                    case 1:
                        sensor = UniquePointer<Sensor> (new SensorHumidity(name, value));
                        break;
                    case 2:
                        sensor = UniquePointer<Sensor> (new SensorLight(name, value));
                        break;
                    case 3:
                        sensor = UniquePointer<Sensor> (new SensorTemperature(name, value));
                        break;
                }
                smartHome.getRooms()[i1]->getDevices()[i2]->addSensor(std::move(sensor));
                SmartHomeManager::writeDataToFile("test_client_server.txt", smartHome);
                if (write(newsockfd, "New sensor added successfully\n", 30) < 0) error("Error writing to socket");
            } else {
                // Write device types
                message = "1. AC unit\n2. Fan\n3. Lightbulb\n\n";
                if (write(newsockfd, message.c_str(), message.size()) < 0) error("Error writing to socket");

                // Read device type
                readNewData(newsockfd, buffer2);
                type = strtol(buffer2, nullptr, 10);

                // Read device name
                readNewData(newsockfd, buffer2);
                name = buffer2;

                // Read device state
                readNewData(newsockfd, buffer2, false);
                state = strcmp(buffer2, "on") == 0 ? true : false;

                // Add new device
                UniquePointer<Device> device;
                switch (type) {
                    case 1:
                        device = UniquePointer<Device> (new DeviceAcUnit(name, state));
                        break;
                    case 2:
                        device = UniquePointer<Device> (new DeviceFan(name, state));
                        break;
                    case 3:
                        device = UniquePointer<Device> (new DeviceLightbulb(name, state));
                        break;
                }
                smartHome.getRooms()[i1]->addDevice(std::move(device));
                SmartHomeManager::writeDataToFile("test_client_server.txt", smartHome);
                if (write(newsockfd, "New device added successfully\n", 30) < 0) error("Error writing to socket");
            }
        } else if (strcmp(buffer, "remove device") == 0 || strcmp(buffer, "remove sensor") == 0) { 
        // REMOVE ENTITY
            int index1, index2;
            // Write rooms
            auto& rooms = writeRooms(smartHome, newsockfd);
            
            // Read room index
            i1 = readIndex(newsockfd, buffer2);

            // Write devices from room
            auto& devices = writeDevices(rooms[i1], newsockfd);

            // Read device index
            i2 = readIndex(newsockfd, buffer2);

            if (strcmp(buffer, "remove sensor") == 0) {
                // Write sensor from device
                auto& sensors = writeSensor(devices[i2], newsockfd);

                // Read sensor index
                readIndex(newsockfd, buffer2);

                // Remove sensor
                smartHome.getRooms()[i1]->getDevices()[i2]->removeSensor(strtol(buffer2, nullptr, 10) - 1);
                SmartHomeManager::writeDataToFile("test_client_server.txt", smartHome);
                if (write(newsockfd, "Successfully removed sensor", 27) < 0) error("Error writing to socket");
            } else {
                // Remove device
                smartHome.getRooms()[i1]->removeDevice(i2);
                SmartHomeManager::writeDataToFile("test_client_server.txt", smartHome);
                if (write(newsockfd, "Successfully removed device", 27) < 0) error("Error writing to socket");
                SmartHomeManager::writeDataToFile("test_client_server.txt", smartHome);
            }
        }
        readNewData(newsockfd, buffer, false);
    }
    close(newsockfd);
    close(sockfd);
    return 0; 
}