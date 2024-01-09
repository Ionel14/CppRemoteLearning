// I implemented the setters for each class, the id is considered the unique identifier for each class so it's constant
// the parameters for setters are constant references to avoid the useless copies or the modification of the parameter inside of the function
// I used the constant references for the functions to avoid useless copies
// I sticked to the rule of 0 because for now I do not explicitly manage dinamic allocations

#include "smarthome.h"
#include "myuniqueptr.h"
#include <fstream>
#include <iostream>
#include <memory>

namespace smartHome{
    SmartHome::SmartHome(const std::vector<Room>& rooms)
        : rooms(rooms) {}

    const std::vector<Room>& SmartHome::getRooms() const {
        return rooms;
    }

    // Factory function
    MyUniquePtr<Sensor> createSensor(const std::string& sensorType, const std::string& sensorId, double value, bool isFunctional) {
        Sensor* sensor;
        if (sensorType == "Temperature") {
            sensor = new TemperatureSensor(sensorId, value, isFunctional);
        } else if (sensorType == "Motion") {
            sensor = new MotionSensor(sensorId, value, isFunctional);
        } else if (sensorType == "Sound") {
            sensor = new SoundSensor(sensorId, value, isFunctional);
        }
        else{
            sensor = nullptr;
        }

        return MyUniquePtr<Sensor>(sensor);
    }

    MyUniquePtr<Device> createDevice(const std::string& deviceType, const std::string& deviceId, bool status, const std::vector<Sensor*>& sensors) {
        Device* device = nullptr;
        if (deviceType == "Thermostat") {
            device = new ThermostatDevice(deviceId, status, sensors);
        } else if (deviceType == "Security") {
            device = new SecurityDevice(deviceId, status, sensors);
        } else if (deviceType == "VoiceControl") {
            device = new VoiceControlDevice(deviceId, status, sensors);
        }

        return MyUniquePtr<Device>(device);
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
            std::vector<Device*> devices;

            while (file >> deviceType >> deviceId >> deviceStatus) {
                std::vector<Sensor*> sensors;

                while (file >> sensorType >> sensorValue >> sensorFunctional) {
                    // Create appropriate Sensor object based on type
                    MyUniquePtr<Sensor> newSensor = createSensor(sensorType, deviceId, sensorValue, sensorFunctional);
                    sensors.push_back(newSensor.release());

                    char nextChar;
                    file >> nextChar; // read the separator or the end of the line
                    if (nextChar == '\n') {
                        break;
                    }
                }

                // Create appropriate Device object based on type
                MyUniquePtr<Device> newDevice = createDevice(deviceType, deviceId, deviceStatus, sensors);
                devices.push_back(newDevice.release());

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
                file << "  " << device->getType() << " " << device->getId() << " " << device->getStatus() << "\n";

                for (const auto& sensor : device->getSensors()) {
                    file << "    " << sensor->getType() << " " << sensor->getValue() << " " << sensor->getIsFunctional() << "\n";
                }
            }
        }

        file.close();
    }

    void printStatus(smartHome::SmartHome home){
        for(const auto& room : home.getRooms()){
            for(const auto& device : room.getDevices()){
                std::cout << "For room " << room.getName() << " the device " << device->getId() << " has status: ";
                if(device->getStatus()){
                    std::cout << "active" << std::endl;
                }
                else{
                    std::cout << "inactive" << std::endl;
                }
                for(const auto& sensor : device->getSensors()){
                    std::cout << "For the current device the sensor " << sensor->getID() << " is: ";
                    if(sensor->getIsFunctional()){
                        std::cout << "functional." << std::endl;
                    }
                    else{
                        std::cout << "not functioning properly." << std::endl;
                    }
                }
            }
        }
    }
}

int main(){

    // Create sensors
    smartHome::Sensor* sensor1 = new smartHome::TemperatureSensor("T1", 25.0, true);
    smartHome::Sensor* sensor2 = new smartHome::MotionSensor("M1", 0.0, true);
    smartHome::Sensor* sensor3 = new smartHome::TemperatureSensor("T2", 15.0, false);
    smartHome::Sensor* sensor4 = new smartHome::SoundSensor("S1", 70.0, true);
    smartHome::Sensor* sensor5 = new smartHome::SoundSensor("S2", 40.0, true);
    smartHome::Sensor* sensor6 = new smartHome::MotionSensor("M2", 1.0, true);

    // Create devices
    std::vector<smartHome::Sensor*> device1Sensors;
    device1Sensors.push_back(sensor1);
    device1Sensors.push_back(sensor3);
    std::vector<smartHome::Sensor*> device2Sensors;
    device2Sensors.push_back(sensor2);
    device2Sensors.push_back(sensor6);
    std::vector<smartHome::Sensor*> device3Sensors;
    device3Sensors.push_back(sensor4);
    device3Sensors.push_back(sensor5);
    std::vector<smartHome::Sensor*> device4Sensors;
    device4Sensors.push_back(sensor1);

    smartHome::Device* device1 = new smartHome::ThermostatDevice("D1", true, device1Sensors);
    smartHome::Device* device2 = new smartHome::SecurityDevice("D2", false, device2Sensors);
    smartHome::Device* device3 = new smartHome::VoiceControlDevice("D3", true, device3Sensors);
    smartHome::Device* device4 = new smartHome::ThermostatDevice("D4", true, device4Sensors);
    smartHome::Device* device5 = new smartHome::VoiceControlDevice("D5", false, std::vector<smartHome::Sensor*>{});

    // Create rooms
    std::vector<smartHome::Device*> room1Devices;
    room1Devices.push_back(device1);
    std::vector<smartHome::Device*> room2Devices;
    room2Devices.push_back(device3);
    room2Devices.push_back(device4);
    std::vector<smartHome::Device*> room3Devices;
    room3Devices.push_back(device5);
    std::vector<smartHome::Device*> room4Devices;
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