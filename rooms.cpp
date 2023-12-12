#include "rooms.h"

#include <fstream>
#include <regex>
#include <string>


void Rooms::modifyRoomNumericData(std::string room, std::string sensor, int value) {
  rooms[room].modifyPrefferedValue(sensor, value);
} 

void Rooms::modifyRoomOnOffData(std::string room, std::string device, bool state) {
  rooms[room].turnDeviceOnOrOff(device, state);
}

void Rooms::readDataFromFile(std::string filename) {
  std::ifstream myFile;
  myFile.open(filename);

  std::string line;
  std::string currentRoom;

  while (!myFile.eof()) {
    std::getline(myFile, line);

    if (line == "")
      continue;

    std::string word = "";
    std::string words[2];

    for (auto x : line) {
      if (x == ' ' || x == '\t') {
          words[0] = word;
          word = "";
      }
      else {
          word += x;
      }
    }
    words[1] = word;

    if (words[0] == "Room:") {
      currentRoom = words[1];
    } else {
      if (std::regex_match( words[1], std::regex( ( "^\\d+$" ) ) )) { // number
        modifyRoomNumericData(currentRoom, words[0], stoi(words[1]));
      } else {
        int state;
        if (words[1] == "off") {
          state = 0;
        } else {
          state = 1;
        }
        modifyRoomOnOffData(currentRoom, words[0], state);
      }
    }
  }
  myFile.close();
}

void Rooms::writeDataToFile(std::string filename) {
  std::ofstream myFile;
  myFile.open(filename);
  for (auto i : rooms) {
    myFile << "Room: " << i.first << std::endl;
    myFile << i.second.convertDataToString();
  }
  myFile.close();
}