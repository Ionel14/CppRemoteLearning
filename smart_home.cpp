#include "smart_home.h"

namespace smart_home
{

void SmartHome::GetDataFromXml(const char* filename) {
    tinyxml2::XMLDocument xmlDoc;
    tinyxml2::XMLError err = xmlDoc.LoadFile(filename);
    if (err != tinyxml2::XML_SUCCESS) {
        throw std::invalid_argument("Error loading file!");
    }

     tinyxml2::XMLNode* pRoot = xmlDoc.RootElement();
    if (pRoot == nullptr) {
        throw std::invalid_argument("Invalid XML format!");
    }

    tinyxml2::XMLElement* pRoomElement = pRoot->FirstChildElement();
    
    if (pRoomElement == nullptr) {
        throw std::invalid_argument("Room element is null!");
    }

    for (pRoomElement; pRoomElement != nullptr; pRoomElement = pRoomElement->NextSiblingElement("Room")) {
        MyUniquePtr<Room> room(new Room());
        
        if(const char* roomName = pRoomElement->Attribute("name")){
            room->SetName(std::string(roomName));
        }
        else
        {
            throw std::invalid_argument("Room name wasn't found!");
        }

        //Get sensors
        for (tinyxml2::XMLElement* sensorElement = pRoomElement->FirstChildElement("HumiditySensor"); sensorElement != nullptr; sensorElement = sensorElement->NextSiblingElement("Sensor")) {
            room->AddSensor(std::move(MyUniquePtr<Sensor>(new HumiditySensor(sensorElement))));
        }

        for (tinyxml2::XMLElement* sensorElement = pRoomElement->FirstChildElement("PresenceSensor"); sensorElement != nullptr; sensorElement = sensorElement->NextSiblingElement("Sensor")) {
            room->AddSensor(std::move(MyUniquePtr<Sensor>(new PresenceSensor(sensorElement))));
        }

        for (tinyxml2::XMLElement* sensorElement = pRoomElement->FirstChildElement("TemperatureSensor"); sensorElement != nullptr; sensorElement = sensorElement->NextSiblingElement("Sensor")) {
            room->AddSensor(std::move(MyUniquePtr<Sensor>(new TemperatureSensor(sensorElement))));
        }

        for (tinyxml2::XMLElement* sensorElement = pRoomElement->FirstChildElement("LightSensor"); sensorElement != nullptr; sensorElement = sensorElement->NextSiblingElement("Sensor")) {
            room->AddSensor(std::move(MyUniquePtr<Sensor>(new LightSensor(sensorElement))));
        }

        //Get devices
        for (tinyxml2::XMLElement* deviceElement = pRoomElement->FirstChildElement("AcUnit"); deviceElement != nullptr; deviceElement = deviceElement->NextSiblingElement("AcUnit")) {
            room->AddDevice(std::move(MyUniquePtr<Device>(new AcUnit(deviceElement))));
        }
         
        for (tinyxml2::XMLElement* deviceElement = pRoomElement->FirstChildElement("Door"); deviceElement != nullptr; deviceElement = deviceElement->NextSiblingElement("Door")) {
            room->AddDevice(std::move(MyUniquePtr<Device>(new Door(deviceElement))));
        }

        for (tinyxml2::XMLElement* deviceElement = pRoomElement->FirstChildElement("LightBulb"); deviceElement != nullptr; deviceElement = deviceElement->NextSiblingElement("LightBulb")) {
            room->AddDevice(std::move(MyUniquePtr<Device>(new LightBulb(deviceElement))));
        }
        rooms_.push_back(std::move(room));
    }
}


// void SmartHome::AddToXml(const std::string &filename)
// {
//     tinyxml2::XMLDocument xmlDoc;
//         tinyxml2::XMLNode* pRoot = xmlDoc.NewElement("SmartHome");
//         xmlDoc.InsertFirstChild(pRoot);

//         for (auto& room : rooms_) {
//             tinyxml2::XMLElement* pRoomElement = xmlDoc.NewElement("Room");
//             pRoomElement->SetAttribute("name", room.GetName().c_str());

//             for (auto& sensor : room.GetSensors()) {
//                 tinyxml2::XMLElement* sensorElement = xmlDoc.NewElement("Sensor");
//                 sensorElement->SetAttribute("name", sensor.GetName().c_str());
//                 sensorElement->SetAttribute("type", sensor.GetType().c_str());
//                 sensorElement->SetAttribute("value", sensor.GetValue());
//                 pRoomElement->InsertEndChild(sensorElement);
//             }

//             for (auto& device : room.GetDevices()) {
//                 tinyxml2::XMLElement* deviceElement = xmlDoc.NewElement("Device");
//                 deviceElement->SetAttribute("name", device.GetName().c_str());
//                 deviceElement->SetAttribute("type", device.GetType().c_str());
//                 deviceElement->SetAttribute("status", device.GetStatus());
//                 pRoomElement->InsertEndChild(deviceElement);
//             }

//             pRoot->InsertEndChild(pRoomElement);
//         }

//         tinyxml2::XMLError eResult = xmlDoc.SaveFile(filename.c_str());
//         if (eResult != tinyxml2::XML_SUCCESS) {
//             throw std::invalid_argument("Error saving to file!");
//         }
// }

std::vector<MyUniquePtr<Room>>& SmartHome::GetRooms()
{
    return rooms_;
}

std::optional<MyUniquePtr<Room>> SmartHome::GetRoom(const std::string &roomName)
{
    for (auto &room : rooms_)
    {
        if (room->GetName() == roomName)
        {
            return std::move(room);
        }
    }
    return std::nullopt;
}

// Sensor& SmartHome::getSensorFromXml(tinyxml2::XMLElement* sensorElement)
// {
//     const char* sensorName = sensorElement->Attribute("name");
//     const char* sensorType = sensorElement->Attribute("type");
//     float sensorValue;
//     sensorElement->QueryFloatAttribute("value", &sensorValue);
//     Sensor* sensor = new Sensor(sensorName, sensorType, sensorValue);
    
//     return *sensor;
// }

// Device& SmartHome::getDeviceFromXml(tinyxml2::XMLElement* deviceElement)
// {
//     const char* deviceName = deviceElement->Attribute("name");
//     const char* deviceType = deviceElement->Attribute("type");
//     bool deviceStatus;
//     deviceElement->QueryBoolAttribute("status", &deviceStatus);
//     Device *device = new Device(deviceName, deviceType, deviceStatus);
    
//     return *device;
// }

} // namespace smart_home
