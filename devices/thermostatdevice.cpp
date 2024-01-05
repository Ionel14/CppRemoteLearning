#include "thermostatdevice.h"
#include <iostream>

namespace smartHome {
    ThermostatDevice::ThermostatDevice(const std::string& deviceId, bool status, const std::vector<Sensor*>& sensors)
        : Device("Thermostat", deviceId, status, sensors) {}

    void ThermostatDevice::powerOn() {
        //exit methode if the device is already functioning
        if(getStatus()){
            return;
        }

        for(const auto& sensor : getSensors()){
            if(sensor->getValue() < 19.0){
                std::cout << "Thermostat device is now active." << std::endl;
                setStatus(true);
                break; //stop checking for an active sensor if one is already found
            }
        }
    }

    void ThermostatDevice::powerOff() {
        //exit methode if the device is already shut down
        if(!getStatus()){
            return;
        }

        bool inactive = true;
        //check if there is any sensor active
        for(const auto& sensor : getSensors()){
            if(sensor->getValue() < 19.0){
                inactive = false;
                break; //stop checking for an active sensor if one is already found
            }
        }

        if(inactive){
            std::cout << "Thermostat device is now inactive." << std::endl;
            setStatus(false);
        }
        else{
            std::cout << "Thermostat device cannot be shut down yet." << std::endl;
        }
    }
}
