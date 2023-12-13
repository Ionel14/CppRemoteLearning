#include "smarthome.h"
#include <fstream>
#include <iostream>

namespace smartHome{
SmartHome::SmartHome(const std::vector<Room> rooms)
    : rooms(rooms) {}

const std::vector<Room> SmartHome::getRooms() const {
    return rooms;
}

void SmartHome::readDataFromFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    rooms.clear(); // Curățăm vectorul existent înainte de a încărca noi date

    std::string roomName, roomId, deviceType, deviceId, sensorType;
    double sensorValue;
    bool deviceStatus, sensorFunctional;

    while (file >> roomName >> roomId) {
        std::vector<Device> devices;

        while (file >> deviceType >> deviceId >> deviceStatus) {
            std::vector<Sensor> sensors;

            while (file >> sensorType >> sensorValue >> sensorFunctional) {
                sensors.emplace_back(sensorType, deviceId, sensorValue, sensorFunctional);
                char nextChar;
                file >> nextChar; // Citiți separatorul sau sfârșitul liniei
                if (nextChar == '\n') {
                    break;
                }
            }

            devices.emplace_back(deviceType, deviceId, deviceStatus, sensors);
            char nextChar;
            file >> nextChar; // Citiți separatorul sau sfârșitul liniei
            if (nextChar == '\n') {
                break;
            }
        }

        rooms.emplace_back(roomName, roomId, devices);
    }

    file.close();
}

void SmartHome::writeDataToFile(const std::string& filename) const {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    for (const auto& room : rooms) {
        file << room.getName() << " " << room.getId() << "\n";

        for (const auto& device : room.getDevices()) {
            file << "  " << device.getType() << " " << device.getId() << " " << device.getStatus() << "\n";

            for (const auto& sensor : device.getSensors()) {
                file << "    " << sensor.getType() << " " << sensor.getValue() << " " << sensor.getIsFunctional() << "\n";
            }
        }
    }

    file.close();
}

int main(){

    //here we will be the actual usage of the aplication
    return 0;
}
}