#ifndef SMART_HOME_H
#define SMART_HOME_H

#include <stdexcept>
#include <unordered_map>

#include "room.h"
#include "TinyXml/tinyxml2.h"
#include "optional"
#include "Sensors/lightsensor.h"
#include "Sensors/humiditysensor.h"
#include "Sensors/presencesensor.h"
#include "Sensors/temperaturesensor.h"
#include "Devices/acunit.h"
#include "Devices/door.h"
#include "Devices/lightbulb.h"

namespace smart_home
{

class SmartHome
{
public:
    void GetDataFromXml(const char* filename);
    // void AddToXml(const std::string &filename);

    std::vector<MyUniquePtr<Room>>& GetRooms();
    std::optional<Room*> GetRoom(const std::string &roomName);

private:
    // Sensor& getSensorFromXml(tinyxml2::XMLElement* sensorElement);
    // Device& getDeviceFromXml(tinyxml2::XMLElement* deviceElement);
    std::vector<MyUniquePtr<Room>> rooms_;
    
};
} // namespace smart_home

#endif