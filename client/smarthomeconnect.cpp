#include "smarthomeconnect.h"


namespace smart_home_client
{


void SmartHomeConnect::StartConnection()
{
    std::unique_ptr<int, SocketDeleter> clientSocket(new int(socket(AF_INET, SOCK_STREAM, 0)));

    if (*clientSocket == -1)
    {
        std::cerr << "Failed to create socket" << std::endl;
        return;
    }
    
	sockaddr_in serverAddress; 
	serverAddress.sin_family = AF_INET; 
	serverAddress.sin_port = htons(8080); 
	serverAddress.sin_addr.s_addr = INADDR_ANY; 

	if(connect(*clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1)
    {
        std::cerr << "Failed to bind socket" << std::endl;
        return;
    } 

    while (true)
    {
        std::string reqStr = RequestString();
        if (reqStr == "X")
        {
            break;
        }
	    sendDataToServer(reqStr.c_str(), clientSocket.get());
    }

	const char* message = ""; 
	int bytesSent = send(*clientSocket, message, strlen(message), 0); 
    if (bytesSent == -1) {
        std::cerr << "Failed to send data to server" << std::endl;
        return;
    }
}

void SmartHomeConnect::sendDataToServer(const char* message, int* clientSocket)
{
    int bytesSent = send(*clientSocket, message, strlen(message), 0); 
    if (bytesSent == -1) {
        std::cerr << "Failed to send data to server" << std::endl;
        return;
    }

    char buffer[1024] = {0};
    int bytesReceived = recv(*clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived == -1) {
        std::cerr << "Failed to receive data from server" << std::endl;
        return;
    }

    std::cout << "\nReceived from server:\n" << buffer << std::endl;
}

std::string SmartHomeConnect::RequestString()
{
    std::cout<<"Menu:\n";
    std::cout<<"Press 1 to get the status of one device/sensor/room/entire home\n";
    std::cout<<"Press 2 to add a new device/sensor\n";
    std::cout<<"Press 3 to remove a device/sensor\n";
    std::cout<<"Press X to close the program\n";

    char input;
    bool next;
    std::string reqStr; 

    do
    {
        next = true;
        std::cin>>input;

        switch (input)
        {
        case '1':
        {
            reqStr = StatusAction();
            break;
        }
        case '2':
        {
            reqStr = AddObject();
            break;
        }
        case '3':
        {
            reqStr = DeleteObject();
            break;
        }
        case 'X':
        {
            return "X";
            break;
        }
        default:
        {
            next = false;
            std::cout<<"Invalid command, please choose one of the options write above\n";
            break;
        }
            
        }
        if (next)
        {
            if (reqStr == "")
            {
                std::cout<<"Choose another action from above\n";
            }
            else
            {
                return reqStr;
            }
        }
        
    }while (!next);
    
    
    return "X";
}

std::string SmartHomeConnect::StatusAction()
{
    std::cout<<"Press 1 to get the status of a device\n";
    std::cout<<"Press 2 to get the status of a sensor\n";
    std::cout<<"Press 3 to get the status of a room\n";
    std::cout<<"Press 4 to get the status of the entire home\n";
    std::cout<<"Press X to abort the action\n";
    
    char input;
    bool next;

    do
    {
        next = true;
        std::cin>>input;

        switch (input)
        {
        case '1':
        {
            return "Status-Device-"+GetAName();
        }
        case '2':
        {
            return "Status-Sensor-"+GetAName();
        }
        case '3':
        {
            return "Status-Room-"+GetAName();
        }
        case '4':
        {
            return "Status-Home";
        }
        case 'X':
        {
            return "";
        }
        default:
        {
            next = false;
            std::cout<<"Invalid command, please choose one of the options write above\n";
            break;
        }
            
        }
    }while (!next);
    return "";
}

std::string SmartHomeConnect::AddObject()
{
    std::cout<<"Press 1 to add a device\n";
    std::cout<<"Press 2 to add a sensor\n";
    std::cout<<"Press X to abort the action\n";
    
    char input;
    bool next;

    do
    {
        next = true;
        std::cin>>input;

        switch (input)
        {
        case '1':
        {
            return "Add-Device-"+GetAName();
        }
        case '2':
        {
            return "Add-Sensor-"+GetAName();
        }
        case 'X':
        {
            return "";
        }
        default:
        {
            next = false;
            std::cout<<"Invalid command, please choose one of the options write above\n";
            break;
        }
            
        }
    }while (!next);
    return "";
}

std::string SmartHomeConnect::DeleteObject()
{
    std::cout<<"Press 1 to delete a device\n";
    std::cout<<"Press 2 to delete a sensor\n";
    std::cout<<"Press X to abort the action\n";
    
    char input;
    bool next;

    do
    {
        next = true;
        std::cin>>input;

        switch (input)
        {
        case '1':
        {
            return "Delete-Device-"+GetAName();
        }
        case '2':
        {
            return "Delete-Sensor-"+GetAName();
        }
        case 'X':
        {
            return "";
        }
        default:
        {
            next = false;
            std::cout<<"Invalid command, please choose one of the options write above\n";
            break;
        }
            
        }
    }while (!next);
    return "";
}

std::string SmartHomeConnect::GetAName()
{
    std::string input;
    char opt;
    do
    {
        std::cout<<"\nType the name of the selected object\n";
        std::cin>>input;

        std::cout<<"Are you sure about the name " + input;
        std::cout<<"\nType N for No, and anything else for yes\n";
        std::cin>>opt;
    } while (opt == 'N');

    return input;
}
}
