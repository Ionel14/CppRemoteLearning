#include "devices_and_sensors.h"

void DevicesAndSensors::modifyPrefferedValue(std::string sensor, int value) {
  numericalDevices[sensor] = value;
}

void DevicesAndSensors::turnDeviceOnOrOff(std::string device, bool state) {
  onOffDevices[device] = state;
}

std::string DevicesAndSensors::convertDataToString() {
  std::string data = "";
  for (auto i : numericalDevices) {
    data += "\t" + i.first + "\t" + std::to_string(i.second) + "\n"; 
  }
  for (auto i : onOffDevices) {
    std::string state;
    if (i.second == 0) {
      state = "off";
    } else {
      state = "on";
    }
    data += "\t" + i.first + "\t" + state + "\n"; 
  }
  return data;
}