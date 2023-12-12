#include "rooms.h"

int main () {
  Rooms rooms1;

  rooms1.modifyRoomNumericData("kitchen", "temperature", 20);
  rooms1.modifyRoomNumericData("kitchen", "humidity", 30);
  rooms1.modifyRoomOnOffData("bedroom01", "lights", 0);
  rooms1.modifyRoomOnOffData("bedroom02", "blinds", 1);

  rooms1.writeDataToFile("data_1.txt");


  Rooms rooms2;

  rooms2.readDataFromFile("data_1.txt");
  rooms2.writeDataToFile("data_2.txt");


  return 0;
}