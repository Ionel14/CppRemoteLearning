#include "smarthomestatus.h"

namespace smart_home
{
    SmartHomeStatus::SmartHomeStatus(std::shared_ptr<std::mutex> mutex): mutex_{mutex}{}

    void SmartHomeStatus::PrintStatus(const std::vector<StatusObject*> &objects, std::string title)
    {
        std::unique_lock<std::mutex> lock(*mutex_.get());

        std::cout<<"_________________"<< std::endl;
        std::cout<< title<< std::endl;
        std::cout<<"_________________"<< std::endl<< std::endl;

        for (StatusObject* object : objects)
        {
            std::cout<<object->Status()<<std::endl<<std::endl; 
        }
        
        std::cout<< std::endl<< std::endl; 
    }


    void SmartHomeStatus::PrintSmartHomeStatus(SmartHome &smartHome)
    {
        std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> timeSpan;

        std::vector<smart_home::MyUniquePtr<smart_home::Room>>& rooms = smartHome.GetRooms();
        while (true)
        {
            for (auto i = 0; i < rooms.size(); i++)
            {
                {
                    std::unique_lock<std::mutex> lock(*mutex_.get());

                    std::cout<<"+++++++++++++++++"<< std::endl;
                    std::cout<<"Room name:"<< rooms[i]->GetName()<< std::endl;
                    timeSpan = std::chrono::high_resolution_clock::now() - startTime;
                    std::cout<< "time since start: "<< timeSpan.count()<< std::endl;
                    std::cout<<"+++++++++++++++++"<< std::endl<< std::endl;

                }
                
                const std::vector<smart_home::StatusObject*> sensors = rooms[i]->GetSensors();
                const std::vector<smart_home::StatusObject*> devices = rooms[i]->GetDevices();


                std::thread sensorsThread([&]() {
                    PrintStatus(sensors, "Sensors");
                    });

                std::thread devicesThread([&]() {
                    PrintStatus(devices, "Devices");
                    });

                sensorsThread.join();
                devicesThread.join();
            }

            std::this_thread::sleep_for(std::chrono::seconds(30));
        }
    }


} // namespace smart_home
