#include <iostream>
#include "client.h"

Client* createClient() {
    std::cout << "Creating new client..." << std::endl;
    return new Client();
}