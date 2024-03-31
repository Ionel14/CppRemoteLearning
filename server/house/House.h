#ifndef NAGARROREMOTELEARNING_HOUSE_H
#define NAGARROREMOTELEARNING_HOUSE_H

#include <vector>
#include <array>
#include "Room.h"

namespace smart_home {
    class House {
    public:
        explicit House(int numRooms);
        std::array<Room, ROOM_NUM> getRooms() const;
        Room getRoom(RoomType roomType) const;
        void writeDataToFile();
        void regenerateSensorValue();

    private:
        std::array<Room, ROOM_NUM> rooms;
        void initializeRooms();
        static std::string getSensorTypeName(const Sensor& sensor);
    };
}
#endif