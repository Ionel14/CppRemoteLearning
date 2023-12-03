#ifndef MOCKCLIENT_H
#define MOCKCLIENT_H

class Client {
public:
    void connect();
    void sendData(const char* data);
    void disconnect();
};

Client* createClient(); 
#endif