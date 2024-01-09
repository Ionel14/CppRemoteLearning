#include "headers/smart_home.h"
#include "headers/smart_home_manager.h"
#include "headers/unique_ptr.h"

#include <fstream>
#include <vector>

using namespace smarthome;

void deallocateSensorsMemory(std::vector<Sensor*>& sensors) {
  for(auto sensor : sensors) {
      delete sensor;
    }
}

void deallocateDevicesMemory(std::vector<Device*>& devices) {
  for(auto device : devices) {
      delete device;
    }
}

void testSmartHome() {
  std::vector<Sensor*> sensors1 = { new SensorTemperature("temperature1", 25), new SensorHumidity("humidity1", 30) };
  std::vector<Sensor*> sensors2 = { new SensorLight("light1", 0) };
  std::vector<Device*> devices1 = { new DeviceAcUnit("ac_unit1", 0, sensors1), new DeviceLightbulb("lightbulb1", 1, sensors2) };

  std::vector<Sensor*> sensors3 = { new SensorTemperature("temperature2", 20), new SensorHumidity("humidity2", 40) };
  std::vector<Device*> devices2 = { new DeviceFan("fan1", 0, sensors3) };

  std::vector<Sensor*> sensors4 = { new SensorLight("light2", 1) };
  std::vector<Device*> devices3 = { new DeviceLightbulb("lightbulb2", 0, sensors4) };

  std::vector<Room> rooms = { Room("bedroom", devices1), Room("living_room", devices2), Room("kitchen", devices3) };

  SmartHome smartHome(rooms);
  SmartHomeManager::writeDataToFile("data1.txt", smartHome);

  SmartHome smartHome2;
  smartHome2 = SmartHomeManager::readDataFromFile("data1.txt");
  SmartHomeManager::writeDataToFile("data2.txt", smartHome2);


  for(auto sensor : sensors1) {
    sensor->printPurpose();
  }
  for(auto sensor : sensors2) {
    sensor->printPurpose();
  }

  for(auto device : devices1) {
    device->printPurpose();
  }
  for(auto device : devices2) {
    device->printPurpose();
  }


  deallocateSensorsMemory(sensors1);
  deallocateSensorsMemory(sensors2);
  deallocateSensorsMemory(sensors3);
  deallocateSensorsMemory(sensors4);

  deallocateDevicesMemory(devices1);
  deallocateDevicesMemory(devices2);
  deallocateDevicesMemory(devices3);
}

void testOperatorStar(const Room&) 
{
    std::cout << "in function testOperatorStar(const Room&)\n";
}

void testUniquePtr() {
  std::cout << " ~ Constructor test\n";
  UniquePtr<Room> up1;
  UniquePtr<Room> up2(nullptr);
  UniquePtr<Room> up3(new Room("roomname"));

  std::cout << up1.get() << std::endl;
  std::cout << up2.get() << std::endl;
  std::cout << up3.get()->getName() << std::endl;

  std::cout << "\n ~ Operator= test\n";
  up1 = std::move(up3);
  up3 = std::move(up2);

  std::cout << up1.get()->getName() << std::endl;
  std::cout << up3.get() << std::endl;

  std::cout << "\n ~ Swap test\n";
  up1.swap(up3);

  std::cout << up1.get() << std::endl;
  std::cout << up3.get()->getName() << std::endl;

  std::cout << "\n ~ Release test\n";
  std::cout << up3.release()->getName() << std::endl;
  std::cout << up3.get() << std::endl;

  std::cout << "\n ~ Reset test\n";
  up3 = std::move(UniquePtr<Room>(new Room("roomname2")));
  std::cout << up3.get()->getName() << std::endl;
  up3.reset(new Room("roomname3"));
  std::cout << up3.get()->getName() << std::endl;

  std::cout << "\n ~ Operator bool test\n";
  std::cout << (up3 ? "not nullptr" : "nullptr") << std::endl;
  up3.release();
  std::cout << (up3 ? "not nullptr" : "nullptr") << std::endl;

  std::cout << "\n ~ Operator* test\n";
  up3 = std::move(UniquePtr<Room>(new Room("roomname4")));
  testOperatorStar(*up3);

  std::cout << "\n ~ Operator[] test\n";
  UniquePtr<int> up4(new int[2]{2, 3});
  std::cout << up4.get()[1] << std::endl;

}

int main () {
  // testSmartHome();
  testUniquePtr();

  return 0;
}
