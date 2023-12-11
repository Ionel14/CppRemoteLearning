#include "room.h"

// Constructor
Room::Room(const std::string& name, const std::string& roomId, const std::vector<Device> devices)
    : name(name), roomId(roomId), devices(devices) {}

// Getter for room's name
const std::string Room::getName() const {
    return name;
}

// Getter for room's id
const std::string Room::getId() const {
    return roomId;
}

// Getter for room's list of devices
const std::vector<Device> Room::getDevices() const {
    return devices;
}
