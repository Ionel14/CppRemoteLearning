#ifndef NAGARROREMOTELEARNING_HOUSE_H
#define NAGARROREMOTELEARNING_HOUSE_H

#include <vector>
#include <array>
#include "Room.h"

namespace smart_home {
    class House {
    public:
        explicit House(int numRooms);
        void writeDataToFile();

    private:
        static const int MAX_ROOMS = 3;
        std::array<Room, MAX_ROOMS> rooms;
        void initializeRooms();

        static std::string getSensorTypeName(const Sensor& sensor);
    };
}
#endif