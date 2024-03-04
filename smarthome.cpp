// I implemented the setters for each class, the id is considered the unique identifier for each class so it's constant
// the parameters for setters are constant references to avoid the useless copies or the modification of the parameter inside of the function
// I used the constant references for the functions to avoid useless copies
// I sticked to the rule of 0 because for now I do not explicitly manage dinamic allocations

#include "smarthome.h"
#include "myuniqueptr.h"
#include "colleagueuniqueptr.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <iomanip>
#include <thread>
#include <chrono>
#include <mutex>
#include <atomic>


namespace smartHome{
    std::mutex gMutex;
    std::atomic<bool> stopPrinting(false);

    SmartHome::SmartHome(const std::vector<Room>& rooms)
        : rooms(rooms) {}

    const std::vector<Room>& SmartHome::getRooms() const {
        return rooms;
    }

    void SmartHome::addRoom(Room room){
        std::lock_guard<std::mutex> lock(gMutex);
        rooms.push_back(room);
    }

    // Factory function
    MyUniquePtr<Sensor> createSensor(const std::string& sensorType, const std::string& sensorId, double value, bool isFunctional) {

        if (sensorType == "Temperature") {
            return MyUniquePtr<Sensor>(new TemperatureSensor(sensorId, value, isFunctional));
        } else if (sensorType == "Motion") {
            return MyUniquePtr<Sensor>(new MotionSensor(sensorId, value, isFunctional));
        } else if (sensorType == "Sound") {
            return MyUniquePtr<Sensor>(new SoundSensor(sensorId, value, isFunctional));
        } else {
            return MyUniquePtr<Sensor>(nullptr);
        }
    }

    UniquePtr<Device> createDevice(const std::string& deviceType, const std::string& deviceId, bool status, const std::vector<Sensor*>& sensors) {
    if (deviceType == "Thermostat") {
        return UniquePtr<Device> (new ThermostatDevice(deviceId, status, sensors));
    } else if (deviceType == "Security") {
        return UniquePtr<Device> (new SecurityDevice(deviceId, status, sensors));
    } else if (deviceType == "VoiceControl") {
        return UniquePtr<Device> (new VoiceControlDevice(deviceId, status, sensors));
    } else {
        return UniquePtr<Device> (nullptr);
    }
}

    void SmartHome::readDataFromFile(const std::string& filename) {
        std::ifstream file(filename);

        if (!file.is_open()) {
            std::cerr << "Error: Unable to open file " << filename << std::endl;
            return;
        }

        std::vector<Room> tempRooms; // Vector temporar pentru a evita modificarea rooms în timpul citirii
        std::string roomName, roomId, deviceType, deviceId, sensorType, sensorId, temp, temp1;
        double sensorValue;
        bool deviceStatus, sensorFunctional;

        while (file >> roomName >> roomId) {
            std::vector<Device*> devices;

            while (file >> deviceType >> deviceId >> deviceStatus) {
                std::vector<Sensor*> sensors;

                while (file >> sensorType >>sensorId >> sensorValue >> sensorFunctional) {
                    // Create appropriate Sensor object based on type
                    MyUniquePtr<Sensor> newSensor = createSensor(sensorType, sensorId, sensorValue, sensorFunctional);
                    sensors.push_back(newSensor.release());

                    char nextChar;
                    file >> nextChar; // read the separator or the end of the line
                    if (nextChar == ';') {
                        break;
                    }
                }

                // Create appropriate Device object based on type
                UniquePtr<Device> newDevice = createDevice(deviceType, deviceId, deviceStatus, sensors);
                devices.push_back(newDevice.release());

                char nextChar;
                file >> nextChar; // read the separator or the end of the line
                if (nextChar == ';') {
                    break;
                }
            }

            tempRooms.emplace_back(roomName, roomId, devices);
        }

        {
            std::lock_guard<std::mutex> lock(gMutex);
            rooms = std::move(tempRooms); 
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
            auto sizeDiv = room.getDevices().size();
            auto devices = room.getDevices();
            
            for (int i=0; i<sizeDiv; i++) {
                file << devices[i]->getType() << " " << devices[i]->getId() << " " << devices[i]->getStatus() << "\n";
                auto sizeSen = devices[i]->getSensors().size();
                auto sensors = devices[i]->getSensors();
                for (int j=0; j<sizeSen; j++) {
                    file << sensors[j]->getType() << " " << sensors[j]->getID() << " " << std::fixed << std::setprecision(1) << sensors[j]->getValue() << " " << sensors[j]->getIsFunctional();
                    if(j == sizeSen -1){
                        file << " ;\n" ;
                    }
                    else{
                        file << " , " ;
                    }
                }
                
                if(i == sizeDiv -1){
                    file << ";\n" ;
                }
                else{
                    file << ",\n" ;
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

    void printStatusPeriodically(SmartHome& home) {
        while (!stopPrinting) {
            {
                std::lock_guard<std::mutex> lock(gMutex);
                printStatus(home); // Call the existing printStatus function
                std::cout << "\n";
            }
            // Wait for 30 seconds before printing again
            std::this_thread::sleep_for(std::chrono::seconds(30));
        }
    }
}

int main(){

    // Create sensors
    smartHome::UniquePtr<smartHome::Sensor> sensor1(new smartHome::TemperatureSensor("T1", 25.0, true));
    smartHome::UniquePtr<smartHome::Sensor> sensor2(new smartHome::MotionSensor("M1", 0.0, true));
    smartHome::UniquePtr<smartHome::Sensor> sensor3(new smartHome::TemperatureSensor("T2", 15.0, false));
    smartHome::UniquePtr<smartHome::Sensor> sensor4(new smartHome::SoundSensor("S1", 70.0, true));
    smartHome::UniquePtr<smartHome::Sensor> sensor5(new smartHome::SoundSensor("S2", 40.0, true));
    smartHome::UniquePtr<smartHome::Sensor> sensor6(new smartHome::MotionSensor("M2", 1.0, true));

    // Create devices
    std::vector<smartHome::Sensor*> device1Sensors = {sensor1.get(), sensor3.get()};
    std::vector<smartHome::Sensor*> device2Sensors = {sensor2.get(), sensor6.get()};
    std::vector<smartHome::Sensor*> device3Sensors = {sensor4.get(), sensor5.get()};
    std::vector<smartHome::Sensor*> device4Sensors = {sensor1.get()};

    smartHome::UniquePtr<smartHome::Device> device1(new smartHome::ThermostatDevice("D1", true, device1Sensors));
    smartHome::UniquePtr<smartHome::Device> device2(new smartHome::SecurityDevice("D2", false, device2Sensors));
    smartHome::UniquePtr<smartHome::Device> device3(new smartHome::VoiceControlDevice("D3", true, device3Sensors));
    smartHome::UniquePtr<smartHome::Device> device4(new smartHome::ThermostatDevice("D4", true, device4Sensors));

    // Create rooms
    std::vector<smartHome::Device*> room1Devices = {device1.get()};
    std::vector<smartHome::Device*> room2Devices = {device3.get(), device4.get()};
    std::vector<smartHome::Device*> room3Devices = {device3.get()};
    std::vector<smartHome::Device*> room4Devices = {device2.get()};

    smartHome::Room room1("LivingRoom", "R1", room1Devices);
    smartHome::Room room2("Bedroom", "R2", room2Devices);
    smartHome::Room room3("Kitchen", "R3", room3Devices);
    smartHome::Room room4("Outside", "R4", room4Devices);
        
    const std::string filename = "home1.txt";
    const smartHome::SmartHome home({room1, room2, room3, room4});
    home.writeDataToFile(filename);
    //const std::string filename = "home1.txt";
    smartHome::SmartHome home1({}); 
    home1.readDataFromFile(filename);
    // Start the printing service on a separate thread
    std::thread printService(smartHome::printStatusPeriodically, std::ref(home1));

    std::this_thread::sleep_for(std::chrono::minutes(1));
    //new room
    smartHome::UniquePtr<smartHome::Sensor> sensor7(new smartHome::TemperatureSensor("T3", 25.0, true));
    smartHome::UniquePtr<smartHome::Sensor> sensor9(new smartHome::TemperatureSensor("T4", 15.0, false));
    std::vector<smartHome::Sensor*> device6Sensors = {sensor7.get(), sensor9.get()};
    smartHome::UniquePtr<smartHome::Device> device6(new smartHome::ThermostatDevice("D6", true, device6Sensors));
    std::vector<smartHome::Device*> room5Devices = {device6.get()};
    smartHome::Room room5("Room", "R5", room5Devices);
    home1.addRoom(room5);

    smartHome::UniquePtr<smartHome::Sensor> sensor8(new smartHome::MotionSensor("M3", 0.0, true));
    std::vector<smartHome::Sensor*> device7Sensors = {sensor8.get()};
    smartHome::UniquePtr<smartHome::Device> device7(new smartHome::SecurityDevice("D7", false, device7Sensors));
    std::vector<smartHome::Device*> room6Devices = {device7.get()};
    smartHome::Room room6("Bedroom", "R6", room6Devices);
    home1.addRoom(room6);

    std::this_thread::sleep_for(std::chrono::minutes(1));
    smartHome::UniquePtr<smartHome::Sensor> sensor10(new smartHome::SoundSensor("S3", 70.0, true));
    std::vector<smartHome::Sensor*> device8Sensors = {sensor10.get(), sensor5.get()};
    smartHome::UniquePtr<smartHome::Device> device8(new smartHome::VoiceControlDevice("D8", true, device8Sensors));
    std::vector<smartHome::Device*> room7Devices = {device8.get()};
    smartHome::Room room7("Outside2", "R7", room7Devices);
    home1.addRoom(room7);
    
    std::this_thread::sleep_for(std::chrono::minutes(1));
    smartHome::stopPrinting = true;

    // Join the printing service thread to avoid termination before it finishes
    printService.join();
    //printStatus(home1);
    return 0;
}