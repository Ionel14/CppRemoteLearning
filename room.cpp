#include "room.h"

namespace smartHome{
// Constructor
Room::Room(const std::string& name, const std::string& roomId, const std::vector<Device>& devices)
    : name(name), roomId(roomId), devices(devices) {}

// Getter for room's name
const std::string& Room::getName() const {
    return name;
}

// Getter for room's id
const std::string& Room::getId() const {
    return roomId;
}

// Getter for room's list of devices
const std::vector<Device>& Room::getDevices() const {
    return devices;
}

//Setters
//there is no setter for the ID because it is suposed to remain the same

void Room::setName(const std::string& newName){
    name = newName;
}

void Room::setDevices(const std::vector<Device>& newDevices){
    devices = newDevices;
}
}