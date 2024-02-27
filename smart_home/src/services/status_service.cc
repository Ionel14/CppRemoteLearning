#include <iostream>
#include <memory>
#include "services/status_service.h"
#include "sensors/temperature_sensor.h"
#include "sensors/presence_sensor.h"
#include "sensors/light_sensor.h"
#include "devices/device.h"

namespace services {

void StatusService::AddSensor(sensors::Sensor* sensor) {
    if (sensor) {
        sensors.push_back(sensor);
    }
}

void StatusService::AddDevice(devices::Device* device) {
    if (device) {
        devices.push_back(device);
    }
}

void StatusService::PrintStatus() {
    std::cout << "Printing the status of sensors:" << std::endl;

    for (auto& sensor : sensors) {
        if (typeid(*sensor) == typeid(sensors::TemperatureSensor)) {
            std::cout << "Temperature sensor room and current temperature: " << sensor->GetRoom()->GetName() << ", " << std::any_cast<float>(sensor->GetData()) << "." << std::endl;
        }
        else if (typeid(*sensor) == typeid(sensors::PresenceSensor)) {
            std::cout << "Presence sensor room and is any presence: " << sensor->GetRoom()->GetName() << ", " << std::boolalpha << std::any_cast<bool>(sensor->GetData()) << "." << std::endl;
        }
        else if (typeid(*sensor) == typeid(sensors::LightSensor)) {
            std::cout << "Light sensor room and light level: " << sensor->GetRoom()->GetName() << ", " << std::any_cast<int>(sensor->GetData()) << "." << std::endl;
        }
    }

    for (auto& device : devices) {
        std::cout << "Device room size and on/off status: " << device->GetRoom()->GetName() << ", " << (device->GetIsOn() ? "on" : "off") << "." 
        << std::endl;
    }
}

} // namespace services

