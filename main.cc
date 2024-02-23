#include "marc_pop_unique_ptr/custom_unique_ptr.h"
#include "devices/Device.h"
#include "user/User.h"

int main() {
    smart_home::User::getInstance().controlDevicesDemo();
    smart_home::User::getUserHouse().writeDataToFile();
    smart_home::User::readSensorDataFromRoomDemo();
    smart_home::User::getInstance().getDevicesStatus();
    return 0;
}
