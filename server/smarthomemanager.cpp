#include "smarthomemanager.h"

namespace smart_home
{

    SmartHomeManager::SmartHomeManager(SmartHome &smart_home): smartHome_{smart_home}, mutex_{std::make_shared<std::mutex> ()} {}

    void SmartHomeManager::Start()
    {
        try
        {
            GetDataFromFile();
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

    void SmartHomeManager::GetDataFromFile()
    {
        std::string filename = "../data_files/data0.xml";
        std::cout<<filename<<std::endl<<std::endl;
        smartHome_.GetDataFromXml( filename.c_str());
    }

   bool SmartHomeManager::getReqFromClient(int *clientSocket)
    {
        char buffer[1024] = {0};
        int bytesReceived = recv(*clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived == 0)
        {
            std::cout<<"Client closed connection";
            return false;
        }
        
        if (bytesReceived <= -1) {
            throw std::invalid_argument("Failed to receive data from server");
            return false;
        }

        std::string aux(buffer);
        std::vector<std::string> requestParam = split(aux, "-");

        aux.clear();
        if (requestParam[0] == "Status")
        {
            if (requestParam[1] == "Sensor")
            {
                if (const std::optional<Sensor*> sensor = smartHome_.GetSensor(requestParam[2]))
                {
                    aux = sensor.value()->Status();
                }
            }

            if (requestParam[1] == "Device")
            {
                if (const std::optional<Device*> device = smartHome_.GetDevice(requestParam[2]))
                {
                    aux = device.value()->Status();
                }
            }

            if (requestParam[1] == "Room")
            {
                if (const std::optional<Room*> room = smartHome_.GetRoom(requestParam[2]))
                {
                    aux = room.value()->Status();
                }
            }

            if (requestParam[1] == "Home")
            {
                aux = smartHome_.Status();
            }
            
        }

        if (requestParam[0] == "Add")
        {
            if (requestParam[1] == "Sensor")
            {
                smartHome_.GetRoom("LivingRoom").value()->AddSensor(MyUniquePtr<Sensor>(new LightSensor(requestParam[2])));
                aux = "Sensor added";
            }

            if (requestParam[1] == "Device")
            {
                smartHome_.GetRoom("LivingRoom").value()->AddDevice(MyUniquePtr<Device>(new Door(requestParam[2])));
                aux = "Device added";
            }
        }

        if (requestParam[0] == "Delete")
        {
            if (requestParam[1] == "Sensor")
            {
                if (smartHome_.DeleteSensor(requestParam[2]))
                {
                    aux = "Sensor Deleted";
                }
            }
            else if (requestParam[1] == "Device")
            {
                if (smartHome_.DeleteDevice(requestParam[2]))
                {
                    aux = "Device Deleted";
                }
            }
            else
            {
                aux = "Object not found";
            }
        }
        
        if (aux.empty())
        {
            aux = "The request was not formated right";
        }
        
        sendDataToClient(aux.c_str(), clientSocket);

        return true;
    }

    void SmartHomeManager::sendDataToClient(const char *message, int *clientSocket)
    {
        int bytesSent = send(*clientSocket, message, strlen(message), 0); 
        if (bytesSent == -1) {
            throw std::invalid_argument("Failed to send data to server");
            return;
        }
    }

    void SmartHomeManager::StartServer()
    {
        try
        {
            GetDataFromFile();
            MyUniquePtr<int, SocketDeleter> server_fd(new int(socket(AF_INET, SOCK_STREAM, 0)));
            
            if (*server_fd == -1) {
                throw std::invalid_argument("Failed to create socket");
                return;
            }

            sockaddr_in serverAddress;
            serverAddress.sin_family = AF_INET;
            serverAddress.sin_port = htons(8080);
            serverAddress.sin_addr.s_addr = INADDR_ANY;

            if(bind(*server_fd, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1)
            {
                throw std::invalid_argument("Failed to bind socket");
                return;
            }

            listen(*server_fd, 5);
            std::cout << "Server listening on port " << 8080 << std::endl;

            MyUniquePtr<int, SocketDeleter> clientSocket(new int(accept(*server_fd, nullptr, nullptr)));

            if (*clientSocket == -1) {
                throw std::invalid_argument("Failed to accept connection");
                return;
            }

            while (getReqFromClient(clientSocket.get()));
            
        }
        catch(const std::invalid_argument& e)
        {
            std::cerr << e.what() << '\n';
        }

    }

    std::vector<std::string> SmartHomeManager::split(std::string input, std::string delimiter)
    {        
        std::vector<std::string> tokens;
        int pos = 0;
        std::string token;

        while((pos = input.find(delimiter)) != std::string::npos){
            token = input.substr(0, pos);
            tokens.push_back(token);
            input.erase(0, pos + 1);
        }

        tokens.push_back(input);

        return tokens;
    }

} // namespace smart_home
