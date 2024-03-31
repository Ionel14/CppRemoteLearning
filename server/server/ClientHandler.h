#ifndef NAGARROREMOTELEARNINGSERVER_CLIENTHANDLER_H
#define NAGARROREMOTELEARNINGSERVER_CLIENTHANDLER_H

namespace smart_home {

    class ClientHandler {
    public:
        static void handleClient(int clientSocketFileDescriptor);
    };

}

#endif
