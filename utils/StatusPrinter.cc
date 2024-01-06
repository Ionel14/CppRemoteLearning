#include "StatusPrinter.h"
#include <fstream>

namespace smart_home {
    void StatusPrinter::printDeviceStatus(const std::vector<Device*> &devices) {
        for (const auto &device : devices) {
            device->displayStatuses();
        }
    }

    void StatusPrinter::printSensorDataFromRoom(RoomType roomType) {
        std::ifstream inFile("house_data.txt");
        if (!inFile.is_open()) {
            std::cerr << "Unable to open file for reading." << std::endl;
            return;
        }

        std::string line;
        bool foundRoom = false;
        std::string roomTypeStr;
        if (roomType == LIVING_ROOM) {
            roomTypeStr = "Living Room";
        } else if (roomType == BEDROOM){
            roomTypeStr = "Bedroom";
        } else if (roomType == KITCHEN){
            roomTypeStr = "Kitchen";
        } else {
            roomTypeStr = "Unknown";
        }

        while (std::getline(inFile, line)) {
            if (line.find("Room Type: " + roomTypeStr) != std::string::npos) {
                foundRoom = true;
                std::cout << line << std::endl;
                while (std::getline(inFile, line) && !line.empty() && line.find("Room Type: ") == std::string::npos) {
                    std::cout << line << std::endl;
                }
                break;
            }
        }

        if (!foundRoom) {
            std::cout << "Room not found." << std::endl;
        }
    }



}