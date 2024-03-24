#ifndef NAGARROREMOTELEARNINGCLIENT_CLIENTUTILS_H
#define NAGARROREMOTELEARNINGCLIENT_CLIENTUTILS_H

void communicateWithServer(int socketFileDescriptor, const std::string& message) {
    send(socketFileDescriptor, message.c_str(), message.length(), 0);
    std::cout << "Sent to server: " << message << std::endl;

    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    int bytesRead = recv(socketFileDescriptor, buffer, sizeof(buffer) - 1, 0);
    if (bytesRead == -1) {
        std::cerr << "Error receiving data" << std::endl;
        return;
    }

    buffer[bytesRead] = '\0';
    std::cout << "Received from server: " << buffer << std::endl;
}

std::string receiveFromServer(int socketFileDescriptor) {
    char buffer[2048];
    memset(buffer, 0, sizeof(buffer));
    int bytesRead = recv(socketFileDescriptor, buffer, sizeof(buffer) - 1, 0);
    if (bytesRead == -1) {
        std::cerr << "Error receiving data" << std::endl;
        return "";
    }

    buffer[bytesRead] = '\0';
    return {buffer};
}

#endif
