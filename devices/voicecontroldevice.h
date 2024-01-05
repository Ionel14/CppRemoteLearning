#ifndef VOICE_CONTROL_DEVICE_H
#define VOICE_CONTROL_DEVICE_H

#include "device.h"

namespace smartHome {
    class VoiceControlDevice : public Device {
    public:
        VoiceControlDevice(const std::string& deviceId, bool status, const std::vector<Sensor*>& sensors);

        void powerOn() override;

        void powerOff() override;

        const std::string& getCommand() const;

        void setCommand(const std::string& newValue);

    private:
        std::string command;

        static const std::string keyword1;
        static const std::string keyword2;
    };
}

#endif // VOICE_CONTROL_DEVICE_H
