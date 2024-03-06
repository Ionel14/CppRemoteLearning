#include <iostream>
#include <memory>
#include <chrono>
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

void StatusService::PrintStatusAsync(int seconds_interval) {
    if (!status_printing_thread.joinable()) {
        should_print_status = true;

        status_printing_thread = std::thread([this, seconds_interval]() {
            while(should_print_status) {
                PrintStatus();

                std::this_thread::sleep_for(std::chrono::seconds(seconds_interval));
            }
        });
    }
    else {
        std::cout << "Status printing has already started." << std::endl;
    }
}

void StatusService::StopPrintStatusAsync() {
    std::cout << "Stopping status printing..." << std::endl;
    should_print_status = false;
    if (status_printing_thread.joinable()) {
        status_printing_thread.join();
    }
    std::cout << "Status printing stopped!" << std::endl;
}

} // namespace services

