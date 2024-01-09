#include <vector>

#include "Sensors/lightsensor.h"
#include "Devices/acunit.h"

#include "Sensors/lightsensor.h"
#include "Devices/acunit.h"
#include "smarthomestatus.h"

#include "uniqueptr.h"

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

        smart_home::UniquePtr<int> ptr1(new int(1));
        smart_home::UniquePtr<int> ptr2(new int(3));
        
        smart_home::UniquePtr<int> arr(new int[3]{1,2,3});

        smart_home::UniquePtr<int> ptr3 = nullptr;

        std::cout<< *ptr1<<' '<< *ptr2<<std::endl;

        ptr1.swap(ptr2);

        std::cout<< *ptr1<<' '<< *ptr2 << arr[1]<< std::endl;

        smart_home::UniquePtr<smart_home::LightSensor> light
        (new smart_home::LightSensor("Light", 600));

        if (light)
        {
            std::cout<< std::endl<<light->GetIntensity()<< std::endl;
        }
        
        light.reset();
        
        if (light)
        {
            std::cout<< std::endl<<light->GetIntensity()<< std::endl;
        }

        light.release();
        
        if (light)
        {
            std::cout<< std::endl<<light->GetIntensity()<< std::endl;
        }
        
        smart_home::UniquePtr<smart_home::AcUnit> ac(new smart_home::AcUnit("ac"));
        // std::vector<smart_home::StatusObject*> obj;

        // obj.push_back(&light);
        // obj.push_back(&ac);

        // smart_home::SmartHomeStatus::PrintSensorsStatus(obj);

    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}