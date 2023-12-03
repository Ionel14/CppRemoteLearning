#include "client.h"
#include <iostream>

void Client::connect() {
    std::cout << "Connecting..." << std::endl;
}

void Client::sendData(const char* data) {
    std::cout << "Sending data: " << data << std::endl;
}

void Client::disconnect() {
    std::cout << "Disconnecting..." << std::endl;
}