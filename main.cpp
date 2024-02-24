#include <vector>

#include "Sensors/lightsensor.h"
#include "Devices/acunit.h"
#include "smarthomestatus.h"

#include "uniqueptr.h"
#include "andreea_unique_ptr"

int main()
{
    
    smart_home::SmartHome smartHome;
    for (auto i = 0; i < 6; i++)
    {
        try
        {
            std::string filename = "../data_files/data" + std::to_string(i) + ".xml";
            std::cout<<filename<<std::endl<<std::endl;
            smartHome.GetDataFromXml( filename.c_str());
            
            smart_home::MyUniquePtr<smart_home::Room> room = smartHome.GetRoom("LivingRoom").value();

            const std::vector<smart_home::StatusObject*> sensors = room->GetSensors();
            const std::vector<smart_home::StatusObject*> devices = room->GetDevices();

            smart_home::SmartHomeStatus::PrintStatus(sensors);
            smart_home::SmartHomeStatus::PrintStatus(devices);

        }
        catch(const std::invalid_argument& e)
        {
            std::cerr << e.what() << '\n';
        }
        std::cout<<std::endl<<std::endl;
    }
    
    return 0;
}