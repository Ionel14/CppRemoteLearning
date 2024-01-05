#include <iostream>
#include "sensors/temperature_sensor.h"
#include "sensors/presence_sensor.h"
#include "services/temperature_service.h"
#include "services/presence_service.h"
#include "services/status_service.h"
#include "devices/ac_unit.h"
#include "devices/fan.h"
#include "devices/light_bulb.h"
#include "tinyxml2.h"

int main() {

    tinyxml2::XMLDocument read_document;
    tinyxml2::XMLDocument write_document;
    read_document.LoadFile("../resources/read_document.xml");
    write_document.LoadFile("../resources/write_document.xml");

    tinyxml2::XMLNode *node = write_document.NewElement("Temperatures");
    write_document.InsertFirstChild(node);
    tinyxml2::XMLElement *element = write_document.NewElement("Temperature");

    tinyxml2::XMLElement *root_element = read_document.RootElement();
    tinyxml2::XMLElement *temperature_element = root_element->FirstChildElement();
    float temperature = std::stof(temperature_element->GetText());

    services::StatusService *status_service = new services::StatusService();

    rooms::Room* bedroom = new rooms::Room("Bedroom", 5.2f);
    
    std::cout << "Bedroom size: " << bedroom->GetSize() << std::endl;

    sensors::TemperatureSensor* temperature_sensor = new sensors::TemperatureSensor(bedroom);
    sensors::PresenceSensor* presence_sensor = new sensors::PresenceSensor(bedroom);

    std::cout << "Temperature sensor's room's size: " << temperature_sensor->GetRoom()->GetSize() << std::endl;

    std::cout << "Current temperature before initialization: " << std::any_cast<float>(temperature_sensor->GetData()) << std::endl;
    element = write_document.NewElement("Temperature");
    element->SetText(std::to_string(std::any_cast<float>(temperature_sensor->GetData())).c_str());
    node->InsertEndChild(element);

    temperature_sensor->SetData(temperature);

    std::cout << "Current temperature after initialization: " << std::any_cast<float>(temperature_sensor->GetData()) << std::endl;
    element = write_document.NewElement("Temperature");
    element->SetText(std::to_string(std::any_cast<float>(temperature_sensor->GetData())).c_str());
    node->InsertEndChild(element);

    devices::AcUnit* ac_unit = new devices::AcUnit(bedroom);
    devices::Fan* fan = new devices::Fan(bedroom);
    devices::LightBulb* light_bulb = new devices::LightBulb(bedroom);

    services::TemperatureService* temperature_service = new services::TemperatureService();
    services::PresenceService* presence_service = new services::PresenceService();

    temperature_service->AddSensor(temperature_sensor);
    temperature_service->AddDevice(ac_unit);
    temperature_service->AddDevice(fan);

    presence_service->AddSensor(presence_sensor);
    presence_service->AddDevice(light_bulb);

    std::cout << "Number of sensors of temperature service: " << temperature_service->GetSensors().size() << std::endl;
    std::cout << "Number of devices of temperature service: " << temperature_service->GetDevices().size() << std::endl;

    temperature_service->Refresh();

    temperature_element = temperature_element->NextSiblingElement();
    temperature = std::stof(temperature_element->GetText());
    temperature_sensor->SetData(temperature);

    std::cout << "Current temperature after cooling: " << std::any_cast<float>(temperature_sensor->GetData()) << std::endl;
    element = write_document.NewElement("Temperature");
    element->SetText(std::to_string(std::any_cast<float>(temperature_sensor->GetData())).c_str());
    node->InsertEndChild(element);

    temperature_service->Refresh();

    // repeated code
    // a wrapper method can be made in order to reduce duplicate code
    temperature_element = temperature_element->NextSiblingElement();
    temperature = std::stof(temperature_element->GetText());
    temperature_sensor->SetData(temperature);
    element = write_document.NewElement("Temperature");
    element->SetText(std::to_string(std::any_cast<float>(temperature_sensor->GetData())).c_str());
    node->InsertEndChild(element);

    temperature_service->Refresh();
    
    presence_service->Refresh();

    status_service->AddSensor(temperature_sensor);
    status_service->AddSensor(presence_sensor);
    status_service->AddDevice(ac_unit);
    status_service->AddDevice(fan);
    status_service->AddDevice(light_bulb);

    status_service->PrintStatus();

    write_document.SaveFile("../resources/write_document.xml");

    delete temperature_service;
    temperature_service = nullptr;
    delete ac_unit;
    ac_unit = nullptr;
    delete temperature_sensor;
    temperature_sensor = nullptr;
    delete bedroom;
    bedroom = nullptr;

    return 0;
}