#include "User.h"

namespace SmartHome {
    User::User(int numRooms, int numSensorsPerRoom) : userHouse(numRooms, numSensorsPerRoom) {
        devices.push_back(new Device(LIGHT));
        devices.push_back(new Device(HEATER));
    }

    User::User(const User& other) : userHouse(other.userHouse) {
        devices.reserve(other.devices.size());
        for (Device* device : other.devices) {
            devices.push_back(new Device(*device));
        }
    }

    User::User(User&& other) : userHouse(std::move(other.userHouse)), devices(std::move(other.devices)) {
        other.devices.clear();
    }

    User& User::operator=(User&& other) {
        if (this != &other) {
            userHouse = std::move(other.userHouse);

            for (Device* device : devices) {
                delete device;
            }
            devices = std::move(other.devices);
            other.devices.clear();
        }
        return *this;
    }

    User& User::operator=(const User& other) {
        if (this != &other) {
            userHouse = other.userHouse;

            for (Device* device : devices) {
                delete device;
            }
            devices.clear();

            devices.reserve(other.devices.size());
            for (Device* device : other.devices) {
                devices.push_back(new Device(*device));
            }
        }
        return *this;
    }

    User::~User() {
        for (Device *device: devices) {
            delete device;
        }
    }

    void User::controlDevicesDemo() {
        while (true) {
            std::cout << "Enter a device type (0 = Light, 1 = Heater): ";
            int deviceType;
            std::cin >> deviceType;
            if (deviceType == 0 || deviceType == 1) {
                std::cout << "Enter a device status (0 = Off, 1 = On): ";
                int deviceStatus;
                std::cin >> deviceStatus;
                if (deviceStatus == 0 || deviceStatus == 1) {
                    devices[deviceType]->setDeviceStatus(deviceStatus);
                    std::cout << "Device status changed." << std::endl;
                    break;
                } else {
                    std::cout << "Invalid device status." << std::endl;
                }
            } else {
                std::cout << "Invalid device type." << std::endl;
            }
        }
    }

    void User::getDevicesStatus() {
        for (Device *device: devices) {
            device->displayStatuses();
        }
    }

    void User::readSensorDataFromRoom(RoomType roomType) {
        std::ifstream inFile("house_data.txt");
        if (inFile.is_open()) {
            std::string line;
            bool foundRoom = false;

            while (std::getline(inFile, line)) {
                if (line.find("Room Type: ") != std::string::npos) {
                    std::string typeStr = line.substr(11);
                    RoomType currentRoomType;

                    if (typeStr == "Living Room") {
                        currentRoomType = LIVING_ROOM;
                    } else if (typeStr == "Bedroom") {
                        currentRoomType = BEDROOM;
                    } else if (typeStr == "Kitchen") {
                        currentRoomType = KITCHEN;
                    } else {
                        continue;
                    }

                    if (currentRoomType == roomType) {
                        foundRoom = true;
                        std::cout << line << std::endl;
                        while (std::getline(inFile, line) && !line.empty() && line[0] != 'R') {
                            std::cout << line << std::endl;
                        }
                        break;
                    }
                }
            }

            if (!foundRoom) {
                std::cout << "Room not found." << std::endl;
            }

            inFile.close();
        } else {
            std::cerr << "Unable to open file for reading." << std::endl;
        }
    }

    void User::readSensorDataFromRoomDemo() {
        while (true) {
            std::cout << "Enter a room type (0 = Living Room, 1 = Bedroom, 2 = Kitchen): ";
            int roomType;
            std::cin >> roomType;
            if (roomType == 0 || roomType == 1 || roomType == 2) {
                readSensorDataFromRoom(static_cast<RoomType>(roomType));
                break;
            } else {
                std::cout << "Invalid room type." << std::endl;
            }
        }
    }

    House User::getUserHouse() const {
        return userHouse;
    }

    void User::setUserHouse(const House &house) {
        userHouse = house;
    }
}