#include <iostream>
#include "../include/sensors/temperature_sensor.h"
#include "../include/services/temperature_service.h"
#include "../include/devices/ac_unit.h"
#include "../include/tiny_xml/tinyxml2.h"

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

    rooms::Room* bedroom = new rooms::Room(5.2f);
    
    std::cout << "Bedroom size: " << bedroom->GetSize() << std::endl;

    sensors::TemperatureSensor* temperature_sensor = new sensors::TemperatureSensor(bedroom);

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

    services::TemperatureService* temperature_service = new services::TemperatureService();

    temperature_service->AddSensor(temperature_sensor);
    temperature_service->AddDevice(ac_unit);

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