#ifndef SMARTHOME_H
#define SMARTHOME_H

#include <vector>
#include <fstream>
#include <iostream>
#include <memory>
#include <iomanip>
#include <thread>
#include <chrono>
#include <mutex>
#include <atomic>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include "room.h"

namespace smartHome{
    class SmartHome {
    public:
        SmartHome(const std::vector<Room>& rooms);

        const std::vector<Room>& getRooms() const;

        void addRoom(Room room);
        void readDataFromFile(const std::string& filename);
        void writeDataToFile(const std::string& filename) const;
        void printStatus();
        void printRoomStatus(std::string roomID);
        void printDeviceStatus(std::string deviceID);
        void printSensorStatus(std::string sensorID);

    private:
        std::vector<Room> rooms;
        //we could also add a vector for devices that are outside of the house
    };
}
#endif // SMARTHOME_H