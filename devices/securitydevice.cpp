#include "securitydevice.h"
#include <iostream>

namespace smartHome {
    SecurityDevice::SecurityDevice(const std::string& deviceId, bool status, const std::vector<Sensor>& sensors)
        : Device("Security", deviceId, status, sensors) {}

    void SecurityDevice::powerOn() {
        //exit methode if the device is already functioning
        if(getStatus()){
            return;
        }

        for(const auto& sensor : getSensors()){
            if(sensor.getValue() != 0.0){
                std::cout << "Security device is now active." << std::endl;
                setStatus(true);
                return; //stop checking for an active sensor if one is already found
            }
        }
        
    }

    void SecurityDevice::powerOff() {
        //exit methode if the device is already shut down
        if(!getStatus()){
            return;
        }

        bool inactive = true;
        //check if there is any sensor active
        for(const auto& sensor : getSensors()){
            if(sensor.getValue() != 0.0){
                inactive = false;
                break; //stop checking for an active sensor if one is already found
            }
        }

        if(inactive){
            std::cout << "Security device is now inactive." << std::endl;
            setStatus(false);
        }
        else{
            std::cout << "Security device cannot be shut down yet." << std::endl;
        }
    }
}
