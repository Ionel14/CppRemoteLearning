#ifndef SMARTHOME_SMARTHOME_MANAGER_H_
#define SMARTHOME_SMARTHOME_MANAGER_H_

#include "smart_home.h"

#include <iostream>
#include <vector>

namespace smarthome {

class SmartHomeManager {
public:
  static SmartHome readDataFromFile(const std::string& filename);
  static void writeDataToFile(const std::string& filename, SmartHome& smarthome, bool append = false);

  static std::string getStatusHome(SmartHome& smarthome);
  static std::string getStatusRoom(SmartHome& smarthome, int index);

private:
  static constexpr const char *resourses_directory = "resources/";
};

} // namespace smarthome
#endif  // SMARTHOME_SMARTHOME_MANAGER_H_