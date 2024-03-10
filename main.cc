#include "user/User.h"
#include <thread>
#include <mutex>

void statusThread() {
    while (true) {
        {
            std::lock_guard<std::mutex> lock(smart_home::User::getInstance().getMutex());
            smart_home::User::getInstance().demoPrintSensorDataFromLivingRoom();
            smart_home::User::getInstance().getDevicesStatus();
        }
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

int main() {
    smart_home::User::getUserHouse().writeDataToFile();

    std::thread printingThread(statusThread);
    // simulate some time passing by
    std::this_thread::sleep_for(std::chrono::seconds(10));

    {
        std::lock_guard<std::mutex> lock(smart_home::User::getInstance().getMutex());
        smart_home::User::getUserHouse().regenerateSensorValue();
        smart_home::User::getUserHouse().writeDataToFile();
        smart_home::User::getInstance().setHeaterOn();
        smart_home::User::getInstance().setLightOn();
    }

    printingThread.join();
    return 0;
}
