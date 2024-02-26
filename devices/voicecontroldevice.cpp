#include "voicecontroldevice.h"
#include <iostream>

namespace smartHome {
    const std::string VoiceControlDevice::keyword1 = "Activate";
    const std::string VoiceControlDevice::keyword2 = "Shut down";

    VoiceControlDevice::VoiceControlDevice(const std::string& deviceId, bool status, const std::vector<Sensor*>& sensors)
        : Device("VoiceControl", deviceId, status, sensors) {}

    void VoiceControlDevice::powerOn() {
        //exit methode if the device is already functioning
        if(getStatus()){
            return;
        }
        for(const auto& sensor : getSensors()){
            if(sensor->getValue() > 35.0 && keyword1 == getCommand()){
                std::cout << "Voice control device is now active." << std::endl;
                setStatus(true);
                break; //stop checking for an active sensor if one is already found
            }
        }
        
    }

    void VoiceControlDevice::powerOff() {
        //exit methode if the device is already shut down
        if(!getStatus()){
            return;
        }

        std::string keyword = "Shut down";
        for(const auto& sensor : getSensors()){
            if(sensor->getValue() > 35.0 && keyword == getCommand()){
                std::cout << "Voice control device is now inactive." << std::endl;
                setStatus(false);
                break; //stop checking for a shut down reason if one is already found
            }
        }
    }

    const std::string& VoiceControlDevice::getCommand() const{
        return command;
    }

    void VoiceControlDevice::setCommand(const std::string& newValue){
        command = newValue;
    }
}
