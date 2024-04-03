#include "server.h"

namespace smartHome{
    Server::Server(size_t num_threads) : server_fd(new int(socket(AF_INET, SOCK_STREAM, 0))), threadpool(num_threads) {
        if (*server_fd == -1) {
            throw std::invalid_argument("Failed to create socket");
        }

        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(8080);
        serverAddress.sin_addr.s_addr = INADDR_ANY;

        if(bind(*server_fd, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
            throw std::invalid_argument("Failed to bind socket");
        }

        listen(*server_fd, 5);
        std::cout << "Server listening on port " << 8080 << std::endl;
    }

    Server::~Server() {
        // No need to close the socket here because it's managed by MyUniquePtr
    }

    void Server::start() {
        try {
            const std::string& filename = "home1.txt";
            SmartHome home1({}); 
            home1.readDataFromFile(filename);

            while (true) {
                // Acceptarea unei noi conexiuni de la un client la fiecare iterație
                std::shared_ptr<int> clientSocket(new int(accept(*server_fd, nullptr, nullptr)), SocketDeleter());

                if (*clientSocket == -1) {
                    throw std::invalid_argument("Failed to accept connection");
                }

                // Fiecare client este procesat într-un fir de execuție din pool
                threadpool.enqueue([this, clientSocket, &home1] {
                    try {
                        while(getReqFromClient(clientSocket.get(), home1)){

                        }
                    } catch(const std::invalid_argument& e) {
                        std::cerr << e.what() << '\n';
                    }
                });
            }
        } catch(const std::invalid_argument& e) {
            std::cerr << e.what() << '\n';
        }
    }

    std::vector<std::string> Server::split(const std::string& input, const std::string& delimiter) {
        std::vector<std::string> tokens;
        size_t pos = 0;
        size_t prevPos = 0;

        while ((pos = input.find(delimiter, prevPos)) != std::string::npos) {
            tokens.push_back(input.substr(prevPos, pos - prevPos));
            prevPos = pos + delimiter.length();
        }

        // add last token, if exists
        if (prevPos < input.length()) {
            tokens.push_back(input.substr(prevPos));
        }

        return tokens;
    }

    void Server::sendDataToClient(const char *message, int *clientSocket) {
        int bytesSent = send(*clientSocket, message, strlen(message), 0); 
        if (bytesSent == -1) {
            throw std::invalid_argument("Failed to send data to server");
        }
    }

    bool Server::getReqFromClient(int *clientSocket, SmartHome& home) {
        char buffer[1024] = {0};
        int bytesReceived = recv(*clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived == 0) {
            std::cout << "Client closed connection";
            return false;
        }

        if (bytesReceived <= -1) {
            throw std::invalid_argument("Failed to receive data from client");
            return false;
        }

        // Deserialization for the message received
        std::string serializedMessage(buffer, bytesReceived);
        std::istringstream iss(serializedMessage);
        boost::archive::text_iarchive archive(iss);
        Message message;
        archive >> message;
        std::vector<std::string> requestParam = split(message.getText(), "-");

        std::ofstream file("logFile.txt", std::ios::app);


        if (requestParam[0] == "Status") {
            if (requestParam[1] == "sensor") {
                home.printSensorStatus(requestParam[2]);
                sendDataToClient("ok", clientSocket);
            } else if (requestParam[1] == "device") {
                home.printDeviceStatus(requestParam[2]);
                sendDataToClient("ok", clientSocket);
            } else if (requestParam[1] == "room") {
                home.printRoomStatus(requestParam[2]);
                sendDataToClient("ok", clientSocket);
            } else if (requestParam[1] == "house") {
                home.printStatus();
                sendDataToClient("ok", clientSocket);
            }
            file << message.getSenderName() << " " << message.getText() << " " << message.getCurrentDate() << ";\n";
            return true;
        } else if (requestParam[0] == "Add") {
            UniquePtr<Sensor> sensor(new TemperatureSensor("T3", 25.0, true));
            if(requestParam[1] == "sensor"){
                home.getRooms()[0].getDevices()[0]->addSensor(sensor.get());
                sendDataToClient("ok", clientSocket);
            }
            else if (requestParam[1] == "device")
            {
                UniquePtr<Device> device(new ThermostatDevice("D6", true, {sensor.get()}));
                auto room = home.getRooms()[0];
                room.addDevice(device.get());
                sendDataToClient("ok", clientSocket);
            }
            file << message.getSenderName() << " " << message.getText() << " " << message.getCurrentDate() << ";\n";
            return true;
        } else if (requestParam[0] == "Delete") {
            auto room = home.getRooms()[0];
            if(requestParam[1] == "sensor"){
                room.getDevices()[0]->removeSensor("T3");
                sendDataToClient("ok", clientSocket);
            }
            else if (requestParam[1] == "device")
            {
                room.removeDevice("D6");
                sendDataToClient("ok", clientSocket);
            }
            file << message.getSenderName() << " " << message.getText() << " " << message.getCurrentDate() << ";\n";
            return true;
        }
        else if(requestParam[0] == "quit"){
            std::cout << "Client closed connection...";
        }
    }

}
