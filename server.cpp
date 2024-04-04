#include "headers/message.h"
#include "headers/message_manager.h"
#include "headers/smart_home.h"
#include "headers/smart_home_manager.h"
#include "headers/thread_pool.h"
#include "headers/unique_ptr_colleague.h"

#include <charconv>
#include <cstring> 
#include <fstream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h> 
#include <unistd.h>
#include <vector>

using namespace smarthome;


void error(const char *msg, int newsockfd = 0, bool userError = false) {
    std::cerr << msg;
    if (userError) {
        if (write(newsockfd, msg, strlen(msg)) < 0) {
            error("Error writing to socket");
        }
    }
    exit(1);
}

Message deserializeData(char buffer[]) {
    Message message;
    std::istringstream iss(buffer);
    {
        boost::archive::text_iarchive ia(iss);
        ia >> message;
    }
    MessageManager::logRequestToFile("log.txt", message);

    return message;
}

auto& writeRooms(SmartHome& smartHome, int newsockfd) {
    std::string message = "Rooms:\n";
    auto& rooms = smartHome.getRooms();
    for (int i = 0; i < rooms.size(); i++) {
        message += std::to_string(i + 1) + ". " + rooms[i]->getName() + "\n";
    }
    if (write(newsockfd, message.c_str(), message.size()) < 0) {
        error("Error writing to socket");
    }
    return rooms;
}

void checkName(char buffer[]) {
    std::string str = buffer;
    if(str.find_first_not_of("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890_-") != std::string::npos) {
        error("Error wrong name", true);
    }
}

void checkIndex(char buffer[], int min, int max, int newsockfd) {
    int index = strtol(buffer, nullptr, 10);
    std::string str = buffer;
    if ((str.find_first_not_of("0123456789") != std::string::npos || (buffer[0] == '0' && strlen(buffer) != 1)) ||
        (index < min || index > max)) {
        error("Error wrong index", newsockfd, true);
    }
}

int readIndex(char buffer[], int min, int max, int newsockfd) {
    bzero(buffer, 512);
    if (read(newsockfd, buffer, 512) < 0) {
        error("Error reading from socket");
    }
    strcpy(buffer, deserializeData(buffer).getMessage().c_str());
    checkIndex(buffer, min, max, newsockfd);
    return strtol(buffer, nullptr, 10) - 1;
}

auto& writeDevices(UniquePointer<Room>& room, int newsockfd) {
    std::string message = "Devices:\n";
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
    std::string message = "Sensors:\n";
    auto& sensors = device->getSensors();
    for (int i = 0; i < sensors.size(); i++) {
        message += std::to_string(i + 1) + ". " + sensors[i]->getName() + "\n";
    }
    if (write(newsockfd, message.c_str(), message.size()) < 0) {
        error("Error writing to socket");
    }
    return sensors;
}

void readNewData(char buffer[], int newsockfd, bool sendWrite = true) {
    bzero(buffer, 512);
    if (read(newsockfd, buffer, 512) < 0) {
        error("Error reading from socket");
    }
    strcpy(buffer, deserializeData(buffer).getMessage().c_str());
    if (sendWrite) {
        if (write(newsockfd, " ",  1) < 0) {
            error("Error writing to socket"); 
        }
    }    
}

int main(int argc, char *argv[]) {
    // Initialize smarthome
    SmartHome smartHome;
    try {
        smartHome = SmartHomeManager::readDataFromFile("test_client_server.txt");
    } catch (std::exception& e) {
        std::cerr << e.what();
        exit(1);
    }

    //  Initialize server socket
    int sockfd, portno, newsockfd;
    struct sockaddr_in serv_addr, cli_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) error("Error opening socket");

    bzero((char *) &serv_addr, sizeof(serv_addr));
    if (argc == 2) {
        checkIndex(argv[1], 2000, 65535, 0);
        portno = strtol(argv[1], nullptr, 10);
    } else {
        portno = 3000;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
        error("Error on binding");
    listen(sockfd, 5);

    // Create a thread pool
    int n = 3;
    ThreadPool pool(n); 
  
    while (true) {
        for (int i = 0; i < n; ++i) { 
            // Initialize client sockets
            socklen_t clilen = sizeof(cli_addr);
            newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
            if (newsockfd < 0) error("Error on accept");

            // Enqueue tasks for execution 
            pool.enqueue([i, newsockfd, &smartHome] {
                // Communicate with client
                char buffer[512], buffer2[512];
                std::string message;
                int i1, i2;

                // Read first input
                readNewData(buffer, newsockfd, false);

                while (strcmp(buffer, "0") != 0) {
                    // GET STATUS
                    if (strcmp(buffer, "status room") == 0 || strcmp(buffer, "status device") == 0 || strcmp(buffer, "status sensor") == 0) {
                        // Write rooms
                        auto& rooms = writeRooms(smartHome, newsockfd);

                        // Read room index
                        i1 = readIndex(buffer2, 1, rooms.size(), newsockfd);

                        if (strcmp(buffer, "status sensor") == 0 || strcmp(buffer, "status device") == 0) {
                            // Write devices from room
                            auto& devices = writeDevices(rooms[i1], newsockfd);

                            // Read device index
                            i1 = readIndex(buffer2, 1, devices.size(), newsockfd);

                            if (strcmp(buffer, "status sensor") == 0) {
                                // Write sensor from device
                                auto& sensors = writeSensor(devices[i1], newsockfd);

                                // Read sensor index
                                i1 = readIndex(buffer2, 1, sensors.size(), newsockfd);

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
                        i1 = readIndex(buffer2, 1, rooms.size(), newsockfd);

                        if (strcmp(buffer, "add sensor") == 0) {
                            // Write devices from room
                            auto& devices = writeDevices(rooms[i1], newsockfd);
                            
                            // Read device index
                            i2 = readIndex(buffer2, 1, devices.size(), newsockfd);
                            bzero(buffer2, 512);

                            // Write sensor types
                            message = "Sensor types:\n1. Humidity\n2. Light\n3. Temperature\n\n";
                            if (write(newsockfd, message.c_str(), message.size()) < 0) error("Error writing to socket");

                            // Read sensor type
                            readNewData(buffer2, newsockfd);
                            checkIndex(buffer2, 1, 3, newsockfd);
                            type = strtol(buffer2, nullptr, 10);

                            // Read sensor name
                            readNewData(buffer2, newsockfd);
                            checkName(buffer2);
                            name = buffer2;

                            // Read sensor value
                            readNewData(buffer2, newsockfd, false);
                            value = strtol(buffer2, nullptr, 10);

                            // Add new sensor
                            UniquePointer<Sensor> sensor;
                            switch (type) {
                                case 1:
                                    checkIndex(buffer2, 0, 100, newsockfd);
                                    sensor = UniquePointer<Sensor> (new SensorHumidity(name, value));
                                    break;
                                case 2:
                                    checkIndex(buffer2, 0, 100, newsockfd);
                                    sensor = UniquePointer<Sensor> (new SensorLight(name, value));
                                    break;
                                case 3:
                                    checkIndex(buffer2, 0, 50, newsockfd);
                                    sensor = UniquePointer<Sensor> (new SensorTemperature(name, value));
                                    break;
                            }
                            smartHome.getRooms()[i1]->getDevices()[i2]->addSensor(std::move(sensor));
                            SmartHomeManager::writeDataToFile("test_client_server.txt", smartHome);
                            if (write(newsockfd, "New sensor added successfully\n", 30) < 0) error("Error writing to socket");
                        } else {
                            // Write device types
                            message = "Device types:\n1. AC unit\n2. Fan\n3. Lightbulb\n\n";
                            if (write(newsockfd, message.c_str(), message.size()) < 0) error("Error writing to socket");

                            // Read device type
                            readNewData(buffer2, newsockfd);
                            checkIndex(buffer2, 1, 3, newsockfd);
                            type = strtol(buffer2, nullptr, 10);

                            // Read device name
                            readNewData(buffer2, newsockfd);
                            checkName(buffer2);
                            name = buffer2;

                            // Read device state
                            readNewData(buffer2, newsockfd, false);
                            if (strcmp(buffer2, "on") == 0) {
                                state = true;
                            } else if(strcmp(buffer2, "off") == 0) {
                                state = false;
                            } else {
                                error("Error wrong state", newsockfd, true);
                            }

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
                        i1 = readIndex(buffer2, 1, rooms.size(), newsockfd);

                        // Write devices from room
                        auto& devices = writeDevices(rooms[i1], newsockfd);

                        // Read device index
                        i2 = readIndex(buffer2, 1, devices.size(), newsockfd);

                        if (strcmp(buffer, "remove sensor") == 0) {
                            // Write sensor from device
                            auto& sensors = writeSensor(devices[i2], newsockfd);

                            // Read sensor index
                            readIndex(buffer2, 1, sensors.size(), newsockfd);

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
                    } else {
                        error("Error wrong request", newsockfd, true);
                    }
                    readNewData(buffer, newsockfd, false);
                }
            }); 
        } 
    }
    close(newsockfd);
    close(sockfd);
    return 0; 
}