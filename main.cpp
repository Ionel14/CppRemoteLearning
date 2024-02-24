#include "headers/smart_home.h"
#include "headers/smart_home_manager.h"
#include "headers/unique_ptr.h"
#include "headers/unique_ptr_colleague.h"

#include <fstream>
#include <vector>

using namespace smarthome;

void testSmartHome() {
  std::vector<UniquePointer<Sensor>> sensors1, sensors2, sensors3, sensors4;
  try {
    sensors1.push_back(UniquePointer<Sensor> (new SensorTemperature("temperature1", 25)));
    sensors1.push_back(UniquePointer<Sensor> (new SensorHumidity("humidity1", 30)));
    sensors2.push_back(UniquePointer<Sensor> (new SensorLight("light1", 0)));
    sensors3.push_back(UniquePointer<Sensor> (new SensorTemperature("temperature2", 20)));
    sensors3.push_back(UniquePointer<Sensor> (new SensorHumidity("humidity2", 40)));
    sensors4.push_back(UniquePointer<Sensor> (new SensorLight("light2", 1)));
  } catch (std::exception& e) {
    std::cerr << e.what();
    return;
  }

  for(auto& sensor : sensors1) {
    sensor->printPurpose();
  }
  for(auto& sensor : sensors2) {
    sensor->printPurpose();
  }

  std::vector<UniquePointer<Device>> devices1, devices2, devices3;
  devices1.push_back(UniquePointer<Device> (new DeviceAcUnit("ac_unit1", 0, sensors1)));
  devices1.push_back(UniquePointer<Device> (new DeviceLightbulb("lightbulb1", 1, sensors2)));
  devices2.push_back(UniquePointer<Device> (new DeviceFan("fan1", 0, sensors3)));
  devices3.push_back(UniquePointer<Device> (new DeviceLightbulb("lightbulb2", 0, sensors4)));

  for(auto& device : devices1) {
    device->printPurpose();
  }
  for(auto& device : devices2) {
    device->printPurpose();
  }

  std::vector<UniquePointer<Room>> rooms;
  rooms.push_back(UniquePointer<Room> (new Room("bedroom", devices1)));
  rooms.push_back(UniquePointer<Room> (new Room("living_room", devices2)));
  rooms.push_back(UniquePointer<Room> (new Room("kitchen", devices3)));
  
  SmartHome smartHome(rooms);

  try {
    SmartHomeManager::writeDataToFile("data1.txt", smartHome);

    SmartHome smartHome2;
    smartHome2 = SmartHomeManager::readDataFromFile("data1.txt");
    SmartHomeManager::writeDataToFile("data2.txt", smartHome2);
  } catch (std::exception& e) {
    std::cerr << e.what();
  }

  std::cout << "\n\tTesting bad cases\n";

  try {
    UniquePointer<Sensor> test = new SensorTemperature("temperature_test", 225);
  } catch (std::exception& e) {
    std::cerr << e.what();
  }

  try {
    SmartHomeManager::writeDataToFile("doesntexist/text.txt", smartHome);
  } catch (std::exception& e) {
    std::cerr << e.what();
  }

  try {
    SmartHomeManager::readDataFromFile("doesntexist.txt");
  } catch (std::exception& e) {
    std::cerr << e.what();
  }

  try {
    SmartHomeManager::readDataFromFile("nopermission.txt");
  } catch (std::exception& e) {
    std::cerr << e.what();
  }

  try {
    SmartHome test;
    test = SmartHomeManager::readDataFromFile("test1_1.txt");
    SmartHomeManager::writeDataToFile("test1_2.txt", test);
  } catch (std::exception& e) {
    std::cerr << e.what();
  }

  try {
    SmartHome test;
    test = SmartHomeManager::readDataFromFile("test2_1.txt");
    SmartHomeManager::writeDataToFile("test2_2.txt", test);
  } catch (std::exception& e) {
    std::cerr << e.what();
  }

  try {
    SmartHome test;
    test = SmartHomeManager::readDataFromFile("test3_1.txt");
    SmartHomeManager::writeDataToFile("test3_2.txt", test);
  } catch (std::exception& e) {
    std::cerr << e.what();
  }

  try {
    SmartHome test;
    test = SmartHomeManager::readDataFromFile("test4_1.txt");
    SmartHomeManager::writeDataToFile("test4_2.txt", test);
  } catch (std::exception& e) {
    std::cerr << e.what();
  }
}

void testOperatorStar(const Room&) 
{
    std::cout << "in function testOperatorStar(const Room&)\n";
}

void testUniquePtr() {
  std::cout << " ~ Constructor test\n";
  UniquePointer<Room> up1;
  UniquePointer<Room> up2(nullptr);
  UniquePointer<Room> up3(new Room("roomname"));

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
  up3 = std::move(UniquePointer<Room>(new Room("roomname2")));
  std::cout << up3.get()->getName() << std::endl;
  up3.reset(new Room("roomname3"));
  std::cout << up3.get()->getName() << std::endl;

  std::cout << "\n ~ Operator bool test\n";
  std::cout << (up3 ? "not nullptr" : "nullptr") << std::endl;
  up3.reset();
  std::cout << (up3 ? "not nullptr" : "nullptr") << std::endl;

  std::cout << "\n ~ Operator* test\n";
  up3 = std::move(UniquePointer<Room>(new Room("roomname4")));
  testOperatorStar(*up3);

  std::cout << "\n ~ Operator[] test\n";
  UniquePointer<int> up4(new int[2]{2, 3});
  std::cout << up4.get()[1] << std::endl;

}

int main () {
  testSmartHome();
  // testUniquePtr();

  return 0;
}
