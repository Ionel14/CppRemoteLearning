#ifndef SMARTHOME_H
#define SMARTHOME_H

#include "room.h"
#include "myuniqueptr.h"
#include <vector>

namespace smartHome{
class SmartHome {
public:
    SmartHome(const std::vector<Room>& rooms);

    const std::vector<Room>& getRooms() const;

    void readDataFromFile(const std::string& filename);
    void writeDataToFile(const std::string& filename) const;

private:
    std::vector<Room> rooms;
    //we could also add a vector for devices that are outside of the house
};
}
#endif // SMARTHOME_H