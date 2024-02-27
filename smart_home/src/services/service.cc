#include <iostream>
#include "services/service.h"
#include "sensors/sensor.h"
#include "devices/device.h"

namespace services {

sensors::Sensor* Service::GetSensor(rooms::Room* room) {
    for (auto &sensor : GetSensors()) {
        if (sensor->GetRoom().get() == room) {
            return sensor;
        }
    }
}

std::vector<sensors::Sensor*> Service::GetSensors() {
    std::vector<sensors::Sensor*> sensors;

    for (auto& sensor_device : sensor_devices) {
        sensors.push_back(sensor_device.first.get());
    }

    return sensors;
}

std::vector<devices::Device*> Service::GetDevices() {
    std::vector<devices::Device*> devices;

    for (auto& sensor_device : sensor_devices) {
        for (auto& device : sensor_device.second) {
            devices.push_back(device.get());
        }
    }

    return devices;
}

void Service::AddSensor(std::unique_ptr<sensors::Sensor> sensor) {
    if (!sensor) {
            return;
    }

    for (auto& sensor_device : sensor_devices) {
        if (sensor_device.first == sensor or sensor_device.first->GetRoom() == sensor->GetRoom()) {
            std::cout << "Sensor already exists in the same room." << std::endl;
            return;
        }
    }

    sensor_devices.emplace(std::move(sensor), std::vector<std::unique_ptr<devices::Device>>());
}

void Service::AddDevice(std::unique_ptr<devices::Device> device) {
    if (!device) {
        return;
    }

    for (auto& sensor_device : sensor_devices) {
        if (sensor_device.first->GetRoom() == device->GetRoom()) {
            sensor_device.second.push_back(std::move(device));
            return;
        }
    }
}

void Service::SetDevicesOnAuto() {
    for (auto& sensor_device : sensor_devices) {
        for (auto& device : sensor_device.second) {
            device->SetOnAuto(sensor_device.first.get());
        }
    }
}

std::any Service::GetSensorData(rooms::Room* room) {
    for (auto &sensor : GetSensors()) {
        if (sensor->GetRoom().get() == room) {
            return sensor->GetData();
        }
    }
}

void Service::SetSensorData(rooms::Room* room, const std::any &data) {
    for (auto &sensor : GetSensors()) {
        if (sensor->GetRoom().get() == room) {
            sensor->SetData(data);
            return;
        }
    }
}

} // namespace services

