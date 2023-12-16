#ifndef NAGARROREMOTELEARNING_HOUSE_H
#define NAGARROREMOTELEARNING_HOUSE_H

#include <vector>
#include <array>
#include "Room.h"
#include "../devices/Device.h"

namespace SmartHome {
    class House {
    public:
        House(int numRooms, int numSensorsPerRoom);
        void writeDataToFile();
    private:
        static const int MAX_ROOMS = 3;
        std::array<SmartHome::Room, MAX_ROOMS> rooms;
    };
}

#endif