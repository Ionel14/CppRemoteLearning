#ifndef SMARTHOME_DEVICESANDSENSORS_H_
#define SMARTHOME_DEVICESANDSENSORS_H_

#include <iostream>
#include <unordered_map>

class DevicesAndSensors {
  // I'm using maps because I need to store key-value pairs 
  // where the keys represent device or sensors, thus they need to be unique.
  // I'm also using unordered maps because the order of tha data doesnt matter,
  // all of the devices/ sensors need to be checked and applied by the smart home.
  std::unordered_map<std::string, int> numericalDevices;
  std::unordered_map<std::string, bool> onOffDevices;

public:
  void modifyPrefferedValue(std::string sensor, int value);
  void turnDeviceOnOrOff(std::string device, bool state);
  std::string convertDataToString();
};

#endif  // SMARTHOME_DEVICESANDSENSORS_H_