#include "../headers/message_manager.h"

#include <fstream>

namespace smarthome {

void MessageManager::logRequestToFile(const std::string& filename, Message& message) {
  std::ofstream myFile;
  myFile.open(resourses_directory + filename, std::ios_base::app);

  if (!myFile) {
    throw std::invalid_argument("Couldn't create file \"" + filename + "\"\n");
  }

  myFile << message.getName() <<  " " << message.getDate() << std::endl;
  myFile.close();
}

} // namespace smarthome
