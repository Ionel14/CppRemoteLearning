#ifndef NAGARROREMOTELEARNING_USER_H
#define NAGARROREMOTELEARNING_USER_H

#include <fstream>
#include <vector>
#include <ctime>
#include <memory>
#include "../house/House.h"
#include "../devices/Device.h"
#define NUM_ROOMS_IN_HOUSE 3

namespace smart_home {
    class User {
    public:
        User(const User& other) = delete;
        User& operator=(const User& other) = delete;
        User(User&& other) = delete;
        User& operator=(User&& other) = delete;

        static User& getInstance() {
            static User instance(NUM_ROOMS_IN_HOUSE);
            return instance;
        }

        static void readSensorDataFromRoomDemo();
        void controlDevicesDemo();
        void getDevicesStatus();
        static House getUserHouse();

    private:
        explicit User(int numRooms);
        std::vector<std::unique_ptr<Device>> devices;
        smart_home::House userHouse;
        void copyDevices(const User& other);
        void moveDevices(User& other);
    };
}

#endif
