#include "server/Server.h"
#include <iostream>

int main() {
    smart_home::Server server;
    if (!server.initializeSocket()) {
        std::cerr << "Failed to initialize server socket" << std::endl;
        return 1;
    }

    server.run();

    return 0;
}
