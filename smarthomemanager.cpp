#include "smarthomemanager.h"

namespace smart_home
{

    SmartHomeManager::SmartHomeManager(SmartHome &smart_home): smartHome_{smart_home}, mutex_{std::make_shared<std::mutex> ()} {}

    void SmartHomeManager::Start()
    {
        try
        {
            std::string filename = "../data_files/data0.xml";
            std::cout<<filename<<std::endl<<std::endl;
            smartHome_.GetDataFromXml( filename.c_str());
            smart_home::SmartHomeStatus status(mutex_);

            
            std::thread statusThread([this, &status]() {
                    status.PrintSmartHomeStatus(this->smartHome_);

                });

            std::thread doChangesThread([this]() {
                    this->DoChanges();

                });

            statusThread.join();
            doChangesThread.join();
        
        }
        catch(const std::invalid_argument& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    void SmartHomeManager::DoChanges()
    {
        while (true)
        {
            std::cout<<"\n\nIf you want to delete a Sensor/Device press D\n\n";
            
            std::string input;
            smart_home::Room *room = smartHome_.GetRoom("LivingRoom").value();

            do
            {
                std::cin >> input;
            } while (input != "D");
            
            {
                std::unique_lock<std::mutex> lock(*mutex_.get());
                std::cout<<"If you want to delete a Sensor press S\n";
                std::cout<<"If you want to delete a Device press D\n";
                std::cout<<"If you want to abort the operation press anything else\n";

                std::cin >> input;

                if (input == "S")
                {
                    std::cout<<"Please type the sensor name\n";
                    std::cout<<"If you want to abort the operation press X\n";

                    std::cin >> input;
                    if (input != "X")
                    {
                        room->DeleteSensor(input);
                    }
                }

                if (input == "D")
                {
                    std::cout<<"Please type the device name\n";
                    std::cout<<"If you want to abort the operation press X\n";

                    std::cin >> input;
                    if (input != "X")
                    {
                        room->DeleteDevice(input);
                    }
                }
            }
        }
        
        // std::this_thread::sleep_for(std::chrono::seconds(10));

        // smart_home::Room *room = smartHome_.GetRoom("LivingRoom").value();
        // room->AddDevice(smart_home::MyUniquePtr<smart_home::Device>(new smart_home::Door("MainDoor", smart_home::DeviceStatus::kOn)));
        // room->DeleteSensor("LightSensor");
            
        // smart_home::Device* ac = room->GetDevice("Cooler").value();
        // ac->SetName("AC UNIT");

        // std::this_thread::sleep_for(std::chrono::seconds(30));
    }

} // namespace smart_home
