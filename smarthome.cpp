// I implemented the setters for each class, the id is considered the unique identifier for each class so it's constant
// the parameters for setters are constant references to avoid the useless copies or the modification of the parameter inside of the function
// I used the constant references for the functions to avoid useless copies
// I sticked to the rule of 0 because for now I do not explicitly manage dinamic allocations

#include "smarthome.h"
#include <fstream>
#include <iostream>

namespace smartHome{
    SmartHome::SmartHome(const std::vector<Room>& rooms)
        : rooms(rooms) {}

    const std::vector<Room>& SmartHome::getRooms() const {
        return rooms;
    }

    void SmartHome::readDataFromFile(const std::string& filename) {
        std::ifstream file(filename);

        if (!file.is_open()) {
            std::cerr << "Error: Unable to open file " << filename << std::endl;
            return;
        }

        rooms.clear(); // We clean the vector before adding new elements

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
                    file >> nextChar; // read the separator or the end of the line 
                    if (nextChar == '\n') {
                        break;
                    }
                }

                devices.emplace_back(deviceType, deviceId, deviceStatus, sensors);
                char nextChar;
                file >> nextChar; // read the separator or the end of the line 
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

    void printStatus(smartHome::SmartHome home){
        for(const auto& room : home.getRooms()){
            for(const auto& device : room.getDevices()){
                std::cout << "For room " << room.getName() << " the device " << device.getId() << " has status: ";
                if(device.getStatus()){
                    std::cout << "active" << std::endl;
                }
                else{
                    std::cout << "inactive" << std::endl;
                }
                for(const auto& sensor : device.getSensors()){
                    std::cout << "For the current device the sensor " << sensor.getID() << " is: ";
                    if(sensor.getIsFunctional()){
                        std::cout << "functional." << std::endl;
                    }
                    else{
                        std::cout << "not functioning properly." << std::endl;
                    }
                }
            }
        }
    }

    int main(){

        // Create sensors
        smartHome::TemperatureSensor sensor1("T1", 25.0, true);
        smartHome::MotionSensor sensor2("M1", 0.0, true);
        smartHome::TemperatureSensor sensor3("T2", 15.0, false);
        smartHome::SoundSensor sensor4("S1", 70.0, true);
        smartHome::SoundSensor sensor5("S2", 40.0, true);
        smartHome::MotionSensor sensor6("M2", 1.0, true);

        // Create devices
        std::vector<smartHome::Sensor> device1Sensors;
        device1Sensors.push_back(sensor1);
        device1Sensors.push_back(sensor3);
        std::vector<smartHome::Sensor> device2Sensors;
        device2Sensors.push_back(sensor2);
        device2Sensors.push_back(sensor6);
        std::vector<smartHome::Sensor> device3Sensors;
        device3Sensors.push_back(sensor4);
        device3Sensors.push_back(sensor5);
        std::vector<smartHome::Sensor> device4Sensors;
        device4Sensors.push_back(sensor1);

        smartHome::ThermostatDevice device1("D1", true, device1Sensors);
        smartHome::SecurityDevice device2("D2", false, device2Sensors);
        smartHome::VoiceControlDevice device3("D3", true, device3Sensors);
        smartHome::ThermostatDevice device4("D4", true, device4Sensors);
        smartHome::VoiceControlDevice device5("D5", false, std::vector<Sensor>{});

        // Create rooms
        std::vector<smartHome::Device> room1Devices;
        room1Devices.push_back(device1);
        std::vector<smartHome::Device> room2Devices;
        room2Devices.push_back(device3);
        room2Devices.push_back(device4);
        std::vector<smartHome::Device> room3Devices;
        room3Devices.push_back(device5);
        std::vector<smartHome::Device> room4Devices;
        room3Devices.push_back(device2);

        smartHome::Room room1("Living Room", "R1", room1Devices);
        smartHome::Room room2("Bedroom", "R2", room2Devices);
        smartHome::Room room3("Kitchen", "R3", room3Devices);
        smartHome::Room room4("Outside", "R4", room4Devices);
        
        smartHome::SmartHome home({room1, room2, room3, room4});
        printStatus(home);
        //here we will be the actual usage of the aplication
        return 0;
    }
}