#ifndef NAGARROREMOTELEARNING_USER_H
#define NAGARROREMOTELEARNING_USER_H

#include <fstream>
#include <vector>
#include <ctime>
#include <memory>
#include <mutex>
#include "../house/House.h"
#include "../devices/Device.h"
#include "../marc_pop_unique_ptr/custom_unique_ptr.h"

namespace smart_home {
    class User {
    public:
        User(const User& other) = delete;
        User& operator=(const User& other) = delete;
        User(User&& other) = delete;
        User& operator=(User&& other) = delete;

        static User& getInstance() {
            static User instance(ROOM_NUM);
            return instance;
        }

        static void readSensorDataFromRoom();
        void controlDevices();
        std::string getDevicesStatus();
        static House getUserHouse();
        std::string getHouseSensorStatus();
        std::string getRoomSensorStatus(RoomType roomType);
        void addDevice(DeviceType type);
        void removeDevice(DeviceType type);
        std::string getDeviceStatus(DeviceType type);
        void addSensorToRoom(RoomType roomType, const std::string& sensorName);
        void removeSensorFromRoom(RoomType roomType, const std::string& sensorName);
        std::string getSensorStatus(RoomType roomType, const std::string& sensorName);

        std::mutex& getMutex() {
            return userMutex;
        };
    private:
        std::mutex userMutex;
        explicit User(int numRooms);
        std::vector<std::unique_ptr<Device>> devices;
        smart_home::House userHouse;
    };
}

#endif
