#ifndef NAGARROREMOTELEARNING_USER_H
#define NAGARROREMOTELEARNING_USER_H

#include <fstream>
#include <vector>
#include <ctime>
#include "../house/House.h"
#include "../devices/Device.h"

namespace SmartHome {
    class User {
    public:
        User(int numRooms, int numSensorsPerRoom);
        User(const User& other);
        User(User&& other);
        User& operator=(const User& other);
        User& operator=(User&& other);
        ~User();
        void readSensorDataFromRoom(RoomType roomType);
        void readSensorDataFromRoomDemo();
        void controlDevicesDemo();
        void getDevicesStatus();
        House getUserHouse() const;
        void setUserHouse(const House &house);
    private:
        std::vector<Device *> devices;
        SmartHome::House userHouse;

    };
}

#endif