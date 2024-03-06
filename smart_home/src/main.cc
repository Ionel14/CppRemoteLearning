#include <iostream>
#include <memory>
#include <chrono>
#include <thread>
#include "sensors/temperature_sensor.h"
#include "sensors/presence_sensor.h"
#include "services/temperature_service.h"
#include "services/presence_service.h"
#include "services/status_service.h"
#include "devices/ac_unit.h"
#include "devices/fan.h"
#include "devices/light_bulb.h"
#include "custom_memory/unique_ptr_colleague.h"
#include "tinyxml2.h"

int main()
{

    // using namespace std::chrono_literals;
    // std::this_thread::sleep_for(std::chrono::minutes(1));

    try
    {
        tinyxml2::XMLDocument read_document;
        tinyxml2::XMLDocument write_document;
        if (read_document.LoadFile("../resources/read_document.xml") != 0) {
            throw std::runtime_error("Could not load file input file.\n");
        }
        if (write_document.LoadFile("../resources/write_document.xml") != 0) {
            throw std::runtime_error("Could not load output file.\n");
        }

        tinyxml2::XMLNode *node = write_document.NewElement("Temperatures");
        write_document.InsertFirstChild(node);
        tinyxml2::XMLElement *element = write_document.NewElement("Temperature");

        tinyxml2::XMLElement *root_element = read_document.RootElement();
        tinyxml2::XMLElement *temperature_element = root_element->FirstChildElement();
        float temperature = std::stof(temperature_element->GetText());

        custom_memory::UniquePtr<services::StatusService> status_service(new services::StatusService());

        std::shared_ptr<rooms::Room> bedroom = std::make_shared<rooms::Room>("Bedroom", 5.2f);

        // this will throw a runtime exception because name is empty
        // std::shared_ptr<rooms::Room> bedroom = std::make_shared<rooms::Room>("", 5.2f);

        std::cout << "Bedroom size: " << bedroom->GetSize() << std::endl;

        std::unique_ptr<sensors::TemperatureSensor> temperature_sensor = std::make_unique<sensors::TemperatureSensor>(bedroom);
        std::unique_ptr<sensors::PresenceSensor> presence_sensor = std::make_unique<sensors::PresenceSensor>(bedroom);

        // this will throw a runtime exception because room is null
        // std::shared_ptr<sensors::PresenceSensor> presence_sensor = std::make_shared<sensors::PresenceSensor>(nullptr);

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

        std::unique_ptr<devices::AcUnit> ac_unit = std::make_unique<devices::AcUnit>(bedroom);
        std::unique_ptr<devices::Fan> fan = std::make_unique<devices::Fan>(bedroom);
        std::unique_ptr<devices::LightBulb> light_bulb = std::make_unique<devices::LightBulb>(bedroom);

        // this will throw a runtime exception because room is null
        // std::shared_ptr<devices::LightBulb> light_bulb = std::make_shared<devices::LightBulb>(nullptr);

        custom_memory::UniquePtr<services::TemperatureService> temperature_service(new services::TemperatureService());
        custom_memory::UniquePtr<services::PresenceService> presence_service(new services::PresenceService());

        temperature_service->AddSensor(std::move(temperature_sensor));
        temperature_service->AddDevice(std::move(ac_unit));
        temperature_service->AddDevice(std::move(fan));

        presence_service->AddSensor(std::move(presence_sensor));
        presence_service->AddDevice(std::move(light_bulb));

        std::cout << "Number of sensors of temperature service: " << temperature_service->GetSensors().size() << std::endl;
        std::cout << "Number of devices of temperature service: " << temperature_service->GetDevices().size() << std::endl;

        for (auto &sensor : temperature_service->GetSensors()) {
            status_service->AddSensor(sensor);
        }

        for (auto &sensor : presence_service->GetSensors()) {
            status_service->AddSensor(sensor);
        }

        for (auto &device : temperature_service->GetDevices()) {
            status_service->AddDevice(device);
        }

        for (auto &device : presence_service->GetDevices()) {
            status_service->AddDevice(device);
        }

        status_service->PrintStatusAsync(30);

        temperature_service->Refresh();

        temperature_element = temperature_element->NextSiblingElement();
        temperature = std::stof(temperature_element->GetText());
        temperature_service->SetSensorData(bedroom.get(), temperature);

        std::cout << "Current temperature after cooling: " << std::any_cast<float>(temperature_service->GetSensorData(bedroom.get())) << std::endl;
        element = write_document.NewElement("Temperature");
        element->SetText(std::to_string(std::any_cast<float>(temperature_service->GetSensorData(bedroom.get()))).c_str());
        node->InsertEndChild(element);

        temperature_service->Refresh();

        std::this_thread::sleep_for(std::chrono::minutes(1));

        // repeated code
        // a wrapper method can be made in order to reduce duplicate code
        temperature_element = temperature_element->NextSiblingElement();
        temperature = std::stof(temperature_element->GetText());
        temperature_service->SetSensorData(bedroom.get(), temperature);
        element = write_document.NewElement("Temperature");
        element->SetText(std::to_string(std::any_cast<float>(temperature_service->GetSensorData(bedroom.get()))).c_str());
        node->InsertEndChild(element);

        temperature_service->Refresh();

        presence_service->Refresh();

        status_service->StopPrintStatusAsync();

        write_document.SaveFile("../resources/write_document.xml");
    }
    catch(std::exception& ex) {
        std::cout << "Errors encountered:" << std::endl;
        std::cout << ex.what();
    }

    return 0;
}