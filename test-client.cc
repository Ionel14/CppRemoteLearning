#include "client.h"

int main() {
    Client* client = createClient();

    client->connect();
    client->sendData("Hello, World!");
    client->disconnect();

    delete client;

    return 0;
}