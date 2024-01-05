#include <vector>

#include "Sensors/lightsensor.h"
#include "Devices/acunit.h"

#include "smarthomestatus.h"

int main()
{
    smart_home::SmartHome smartHome;
    try
    {
        //smartHome.GetDataFromXml("../data.xml");
        
        //smart_home::Device device("BathroomDoor", "Door", true);
        //smart_home::Sensor presence("PresenceSensor", "Presence", 0);
        
        // smart_home::Room *living = smartHome.GetRoom("LivingRoom");
        // living->AddSensor(presence);
        // living->AddDevice(device);

        //smartHome.GetRoom("LivingRoom")->DeleteSensor("PresenceSensor");

        // smart_home::Sensor *lightSensor = smartHome.GetRoom("LivingRoom")->GetSensor("LightSensor");
        // if (lightSensor != nullptr)
        // {
        //     float val = lightSensor->GetValue();
        //     std::cout<< val;
        //     lightSensor->SetValue(200);
        //     std::cout<<smartHome.GetRoom("LivingRoom")->GetSensor("LightSensor")->GetValue();
        // }

        // smartHome.AddToXml("../data.xml");

        smart_home::LightSensor light("Light", 600);
        smart_home::AcUnit ac("AC");

        std::vector<smart_home::StatusObject*> obj;

        obj.push_back(&light);
        obj.push_back(&ac);

        smart_home::SmartHomeStatus::PrintSensorsStatus(obj);


    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}