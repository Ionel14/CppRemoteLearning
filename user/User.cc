#include "User.h"
#include "../utils/StatusPrinter.h"
#include "../devices/AirConditioner.h"
#include "../devices/Heater.h"
#include "../devices/Light.h"
#include "../marc_pop_unique_ptr/custom_unique_ptr.h"

namespace smart_home {

    enum DeviceChoiceEnum {
        LIGHT = 0,
        HEATER = 1,
        AIR_CONDITIONER = 2,
        EXIT = -1
    };

     User::User(int numRooms) : userHouse(numRooms) {
        devices.push_back(custom_memory::MakeCustomUnique<Light>());
        devices.push_back(custom_memory::MakeCustomUnique<Heater>());
        devices.push_back(custom_memory::MakeCustomUnique<AirConditioner>());
    }

    void User::controlDevicesDemo() {
        while (true) {
            std::cout << "Enter a device type (0 = Light, 1 = Heater, 2 = AirConditioner) or -1 to exit: ";
            int deviceType;
            std::cin >> deviceType;

            if (deviceType == DeviceChoiceEnum::EXIT) {
                break;
            }

            if (deviceType < 0 || deviceType >= devices.size()) {
                std::cout << "Invalid device type. Please try again." << std::endl;
                continue;
            }

            try {
                switch(deviceType) {
                    case DeviceChoiceEnum::LIGHT: {
                        auto* light = dynamic_cast<Light*>(devices[deviceType].Get());
                        if (light) {
                            std::cout << "Enter brightness level (0-100): ";
                            int brightness;
                            std::cin >> brightness;
                            if (brightness < 0 || brightness > 100) throw std::out_of_range("Brightness must be between 0 and 100.");
                            light->setBrightness(brightness);
                        } else throw std::runtime_error("Device is not a Light.");
                        break;
                    }
                    case DeviceChoiceEnum::HEATER: {
                        auto* heater = dynamic_cast<Heater*>(devices[deviceType].Get());
                        if (heater) {
                            std::cout << "Enter temperature: ";
                            int temperature;
                            std::cin >> temperature;
                            heater->setTemperature(temperature);
                        } else throw std::runtime_error("Device is not a Heater.");
                        break;
                    }
                    case DeviceChoiceEnum::AIR_CONDITIONER: {
                        auto* ac = dynamic_cast<AirConditioner*>(devices[deviceType].Get());
                        if (ac) {
                            std::cout << "Enter temperature: ";
                            int temperature;
                            std::cin >> temperature;
                            ac->setTemperature(temperature);
                            std::cout << "Enter mode (1 COOLING, 2 HEATING): ";
                            int mode;
                            std::cin >> mode;
                            if (mode != 1 && mode != 2) throw std::invalid_argument("Invalid mode.");
                            ac->setMode(static_cast<ACMode>(mode));
                        } else throw std::runtime_error("Device is not an AirConditioner.");
                        break;
                    }
                    default:
                        std::cout << "Invalid device type." << std::endl;
                        continue;
                }
                std::cout << "Device settings updated." << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }
    }

    // for simplicity purpose, I chose to make a demo for the thread homework, to avoid complicating with room selection
    void User::demoPrintSensorDataFromLivingRoom(){
        StatusPrinter::printSensorDataFromRoom(RoomType::LIVING_ROOM);
    }

    void User::getDevicesStatus() {
        std::vector<const Device*> rawDevicePointers;
        rawDevicePointers.reserve(devices.size());
        for (const auto& device : devices) {
            rawDevicePointers.push_back(device.Get());
        }
        smart_home::StatusPrinter::printDeviceStatus(rawDevicePointers);
    }

    void User::setLightOn(){
        auto* light = dynamic_cast<Light*>(devices[0].Get());
        light->setDeviceStatus(1);
    }

    void User::setHeaterOn(){
        auto* heater = dynamic_cast<Heater*>(devices[1].Get());
        heater->setDeviceStatus(1);
    }

    void User::readSensorDataFromRoomDemo() {
        while (true) {
            std::cout << "Enter a room type (0 = Living Room, 1 = Bedroom, 2 = Kitchen): ";
            int roomType;
            std::cin >> roomType;
            if (roomType == 0 || roomType == 1 || roomType == 2) {
                StatusPrinter::printSensorDataFromRoom(static_cast<RoomType>(roomType));
                break;
            } else {
                std::cout << "Invalid room type." << std::endl;
            }
        }
    }

    House User::getUserHouse() {
        return House(3);
    }
}
