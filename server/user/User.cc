#include "User.h"
#include "../utils/StatusPrinter.h"
#include "../devices/AirConditioner.h"
#include "../devices/Heater.h"
#include "../devices/Light.h"

void guardDeviceExists(const std::vector<std::unique_ptr<smart_home::Device>>& devices, int deviceType) {
    if (devices[deviceType] == nullptr) {
        std::cout << "Device is not available, you need to add it first" << std::endl;
        throw std::runtime_error("Device is not available.");
    }
}

namespace smart_home {

    enum DeviceChoiceEnum {
        LIGHT = 0,
        HEATER = 1,
        AIR_CONDITIONER = 2,
        EXIT = -1
    };

    User::User(int numRooms) : userHouse(numRooms), devices() {}

    void User::controlDevices() {
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
                        guardDeviceExists(devices, deviceType);
                        auto* light = dynamic_cast<Light*>(devices[deviceType].get());
                        if (light) {
                            std::cout << "Enter brightness level (0-100): ";
                            int brightness;
                            std::cin >> brightness;
                            if (brightness < 0 || brightness > 100) throw std::out_of_range("Brightness must be between 0 and 100.");
                            light->setBrightness(brightness);
                            std::cout << "Device settings updated." << std::endl;

                        } else throw std::runtime_error("Device is not a Light.");
                        break;
                    }
                    case DeviceChoiceEnum::HEATER: {
                        guardDeviceExists(devices, deviceType);
                        auto* heater = dynamic_cast<Heater*>(devices[deviceType].get());
                        if (heater) {
                            std::cout << "Enter temperature: ";
                            int temperature;
                            std::cin >> temperature;
                            heater->setTemperature(temperature);
                            std::cout << "Device settings updated." << std::endl;
                        } else throw std::runtime_error("Device is not a Heater.");
                        break;
                    }
                    case DeviceChoiceEnum::AIR_CONDITIONER: {
                        guardDeviceExists(devices, deviceType);
                        auto* ac = dynamic_cast<AirConditioner*>(devices[deviceType].get());
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
                            std::cout << "Device settings updated." << std::endl;
                        } else throw std::runtime_error("Device is not an AirConditioner.");
                        break;
                    }
                    default:
                        std::cout << "Invalid device type." << std::endl;
                        continue;
                }
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }
    }

    void User::addDevice(DeviceType type) {

        if (type != DeviceType::LIGHT && type != DeviceType::HEATER && type != DeviceType::AIR_CONDITIONER) {
            std::cerr << "Invalid device type." << std::endl;
            throw std::invalid_argument("Invalid device type.");
        }

        std::unique_ptr<Device> newDevice;
        switch (type) {
            case DeviceType::LIGHT:
                newDevice = std::make_unique<Light>();
                break;
            case DeviceType::HEATER:
                newDevice = std::make_unique<Heater>();
                break;
            case DeviceType::AIR_CONDITIONER:
                newDevice = std::make_unique<AirConditioner>();
                break;
            case UNKNOWN_DEVICE:
                break;
        }
        devices.push_back(std::move(newDevice));
    }

    void User::removeDevice(DeviceType type) {

        if (type != DeviceType::LIGHT && type != DeviceType::HEATER && type != DeviceType::AIR_CONDITIONER) {
            std::cerr << "Invalid device type." << std::endl;
            throw std::invalid_argument("Invalid device type.");
        }

        for (size_t i = 0; i < devices.size(); ++i) {
            if (devices[i]->getDeviceType() == getDeviceTypeString(type)) {
                devices.erase(devices.begin() + i);
                return;
            }
        }
        std::cerr << "Device not found." << std::endl;
    }

    std::string User::getDeviceStatus(DeviceType type) {
        for (const auto& device : devices) {
            if (device->getDeviceType() == getDeviceTypeString(type)) {
                return device->displayStatuses();
            }
        }
        std::cerr << "Device not found." << std::endl;
        return "Device not found.";
    }

    std::string User::getDevicesStatus() {
        std::string status;
        for (const auto& device : devices) {
            status += device->displayStatuses() + '\n';
        }
        std::cerr << "Device not found." << std::endl;
        return status;
    }

    void User::readSensorDataFromRoom() {
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

     std::string User::getHouseSensorStatus() {
        std::string status;
        for (const auto& room : userHouse.getRooms()) {
            status += room.displaySensorStatuses() + '\n';
        }
        return status;
    }

    std::string User::getRoomSensorStatus(RoomType roomType) {
        return userHouse.getRoom(roomType).displaySensorStatuses();
    }

    void User::addSensorToRoom(RoomType roomType, const std::string& sensorName) {
        if (parseSensorTypeFromSensorName(sensorName) == SensorType::UNKNOWN_SENSOR) {
            std::cerr << "Invalid sensor name." << std::endl;
            throw std::invalid_argument("Invalid sensor name.");
            return;
        }

        switch (parseSensorTypeFromSensorName(sensorName)) {
            case SensorType::TEMPERATURE:
                userHouse.getRoom(roomType).addTemperatureSensor(sensorName);
                break;
            case SensorType::HUMIDITY:
                userHouse.getRoom(roomType).addHumiditySensor(sensorName);
                break;
            case SensorType::MONOXIDE:
                userHouse.getRoom(roomType).addMonoxideSensor(sensorName);
                break;
            default:
                std::cerr << "Invalid sensor type." << std::endl;
                throw std::invalid_argument("Invalid sensor type.");
        }

        userHouse.getRoom(roomType).addTemperatureSensor(sensorName);
    }

    void User::removeSensorFromRoom(RoomType roomType, const std::string& sensorName) {
        if (parseSensorTypeFromSensorName(sensorName) == SensorType::UNKNOWN_SENSOR) {
            std::cerr << "Invalid sensor name." << std::endl;
            throw std::invalid_argument("Invalid sensor name.");
            return;
        }

        switch (parseSensorTypeFromSensorName(sensorName)) {
            case SensorType::TEMPERATURE:
                userHouse.getRoom(roomType).removeTemperatureSensor(sensorName);
                break;
            case SensorType::HUMIDITY:
                userHouse.getRoom(roomType).removeHumiditySensor(sensorName);
                break;
            case SensorType::MONOXIDE:
                userHouse.getRoom(roomType).removeMonoxideSensor(sensorName);
                break;
            default:
                std::cerr << "Invalid sensor type." << std::endl;
                throw std::invalid_argument("Invalid sensor type.");
        }
    }

    std::string User::getSensorStatus(RoomType roomType, const std::string &sensorName) {
        const auto& sensors = userHouse.getRoom(roomType).getSensors();
        if (sensors.empty()) {
            std::cerr << "No sensors found." << std::endl;
            return "No sensors found.";
        }

        for (const auto& sensor : sensors) {
            std::cout << sensor->getName() << std::endl;
            if (sensor->getName() == sensorName) {
                return sensor->displayStatus();
            }
        }
        std::cerr << "Sensor not found." << std::endl;
        return "Sensor not found.";
    }

    House User::getUserHouse() {
        return House(ROOM_NUM);
    }
}
