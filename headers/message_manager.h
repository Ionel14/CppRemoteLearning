#ifndef SMARTHOME_MESSAGE_MANAGER_H_
#define SMARTHOME_MESSAGE_MANAGER_H_

#include "message.h"

#include <iostream>

namespace smarthome {

class MessageManager {
public:
  static void logRequestToFile(const std::string& filename, Message& message);

private:
  static constexpr const char *resourses_directory = "resources/";
};

} // namespace smarthome
#endif  // SMARTHOME_MESSAGE_MANAGER_H_