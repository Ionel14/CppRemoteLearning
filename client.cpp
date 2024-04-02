#include "headers/message.h"

#include <fstream>
#include <iostream>
#include <netinet/in.h>
#include <netdb.h> 
#include <random>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace smarthome;


void error(const char* msg) {
    std::cerr << msg;
    exit(0);
}

void readData(int sockfd, char buffer[]) {
  bzero(buffer, 512);
  if (read(sockfd, buffer, 512) < 0) {
    error("Error reading from socket");
  }
}

std::ostringstream serializeData(std::string text, std::string name) {
  std::time_t t = std::time(nullptr);
  char date[11];
  std::strftime(date, sizeof(date), "%F", std::localtime(&t));

  const Message message(text, name, date);

  std::ostringstream oss;
  {
    boost::archive::text_oarchive oa(oss);
    oa << message;
  }

  return oss;
}

void writeData(int sockfd, const char buffer[], std::string name) {
  std::ostringstream oss = serializeData(buffer, name);
  if (write(sockfd, oss.str().c_str(), oss.str().length()) < 0) {
    error("Error writing to socket");
  }
}

int countOptions(char buffer[]) {
  int n = 0;
  for(int i = 0; i < strlen(buffer); i++) {
    if(buffer[i] == '.') {
      n++;
    }
  }
  return n;
}

int readNumberInInterval(std::string message, int min, int max) {
  std::string input;
  std::cout << message;
  getline(std::cin, input);
  while((input.find_first_not_of("0123456789") != std::string::npos || (input[0] == '0' && input.size() != 1)) ||
    (stoi(input) < min || stoi(input) > max)) {
    std::cout << "\nIncorrect input. Please write a number between " << min << " and " << max << "\n\n" + message;
    getline(std::cin, input);
  }
  return stoi(input);
}

void readAnswer(char buffer[], int& input) {
  printf("%s\n", buffer);
  input = readNumberInInterval("Answer: ", 1, countOptions(buffer));
  std::cout << std::endl;
}

std::string readStringName(std::string message) {
  std::string input;
  std::cout << message;
  getline(std::cin, input);
  while(input.find_first_not_of("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890_-") != std::string::npos) {
    std::cout << "\nIncorrect input. Please write a name consisting of only letters, numbers, \"_\" or \"-\"\n\n" << message;
    getline(std::cin, input);
  }
  return input;
}


int main(int argc, char *argv[]) {
  std::random_device rd;
  std::string name = "client" + std::to_string(rd());

  int sockfd, portno;
  struct sockaddr_in serv_addr;
  struct hostent *server;

  char buffer[512];
  std::string message;
  int input, input2;
  std::string inputStr, inputStr2;

  if (argc == 2) {
    portno = strtol(argv[1], nullptr, 10);
    std::string str = argv[1];
      if ((str.find_first_not_of("0123456789") != std::string::npos || (buffer[0] == '0' && strlen(buffer) != 1)) ||
          (portno < 2000 || portno > 65535)) {
          error("Error wrong port number");
      }
  } else {
    portno = 3000;
  }
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) 
    error("Error opening socket");
  server = gethostbyname("reni");
  if (server == NULL)
    error("Error, no such host\n");
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
  serv_addr.sin_port = htons(portno);
  if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
    error("Error connecting");


  std::cout << "Choose option:\n0.Exit\n1. Get status\n2. Add new entity\n3. Remove entity\n\n";
  input = readNumberInInterval("Answer: ", 0, 3);
  std::cout << std::endl;
  bzero(buffer, 512);
  while (input != 0) {
    switch(input) {
      case 1: // Get status
        std::cout << "Get status of:\n1. Sensor\n2. Device\n3. Room\n4. Home\n\n";
        input = readNumberInInterval("Answer: ", 1, 4);
        std::cout << std::endl;

        // Write get status request
        switch (input) {
          case 1:
            strcpy(buffer, "status sensor");
            break;
          case 2:
            strcpy(buffer, "status device");
            break;
          case 3:
            strcpy(buffer, "status room");
            break;
          case 4:
            strcpy(buffer, "status home");
            break;
        }
        writeData(sockfd, buffer, name);

        if (input == 1 || input == 2 || input == 3) {
          // Read rooms
          readData(sockfd, buffer);

          // Write room index
          readAnswer(buffer, input2);
          writeData(sockfd, std::to_string(input2).c_str(), name);

          if (input == 1 || input == 2) {
            // Read devices
            readData(sockfd, buffer);

            // Write device index
            readAnswer(buffer, input2);
            writeData(sockfd, std::to_string(input2).c_str(), name);

            if(input == 1) {
              // Read sensors
              readData(sockfd, buffer);

              // Write sensor index
              readAnswer(buffer, input2);
              writeData(sockfd, std::to_string(input2).c_str(), name);
            }
          }
        }
        // Read status
        readData(sockfd, buffer);
        printf("%s\n", buffer);
        break;
      case 2: // Add new entity
        std::cout << "Add new:\n1. Sensor\n2. Device\n\n";
        input = readNumberInInterval("Answer: ", 1, 2);
        std::cout << std::endl;

        // Write add new entity request
        switch (input) {
          case 1:
            strcpy(buffer, "add sensor");
            break;
          case 2:
            strcpy(buffer, "add device");
            break;
        }
        writeData(sockfd, buffer, name);

        // Read rooms
        readData(sockfd, buffer);

        // Write room index
        readAnswer(buffer, input2);
        writeData(sockfd, std::to_string(input2).c_str(), name);

        if (input == 1) {
          // Read devices
          readData(sockfd, buffer);

          // Write device index
          readAnswer(buffer, input2);
          writeData(sockfd, std::to_string(input2).c_str(), name);

          // Read sensor types
          readData(sockfd, buffer);

          // Write sensor type
          readAnswer(buffer, input2);
          writeData(sockfd, std::to_string(input2).c_str(), name);

          inputStr = readStringName("Sensor name: ");
          inputStr2 = std::to_string(readNumberInInterval("Sensor value: ", 0, input2 == 3 ? 50 : 100));
          std::cout << std::endl;

        } else {
          // Read device types
          readData(sockfd, buffer);

          // Write device type
          readAnswer(buffer, input2);
          writeData(sockfd, std::to_string(input2).c_str(), name);

          inputStr = readStringName("Device name: ");

          std::cout << "Device state (on/ off): ";
          getline(std::cin, inputStr2);
          while(inputStr2 != "on" && inputStr2 != "off") {
            std::cout << "\nIncorrect input. Please write \"on\" or \"off\"\n\nDevice state (on/ off): ";
            getline(std::cin, inputStr2);
          }
          std::cout << std::endl;
        }
        // Write name
        readData(sockfd, buffer);
        writeData(sockfd, inputStr.c_str(), name);

        // Write value/ state
        readData(sockfd, buffer);
        writeData(sockfd, inputStr2.c_str(), name);

        // Read message
        readData(sockfd, buffer);
        printf("%s\n", buffer);
        break;
      case 3: // Remove entity
        std::cout << "Remove:\n1. Sensor\n2. Device\n\n";
        input = readNumberInInterval("Answer: ", 1, 2);
        std::cout << std::endl;

        // Write remove entity request
        switch (input) {
          case 1:
            strcpy(buffer, "remove sensor");
            break;
          case 2:
            strcpy(buffer, "remove device");
            break;
        }
        writeData(sockfd, buffer, name);

        // Read rooms
        readData(sockfd, buffer);

        // Write room index
        readAnswer(buffer, input2);
        writeData(sockfd, std::to_string(input2).c_str(), name);
        
        // Read devices
        readData(sockfd, buffer);

        // Write device index
        readAnswer(buffer, input2);
        writeData(sockfd, std::to_string(input2).c_str(), name);

        if(input == 1) {
          // Read sensors
          readData(sockfd, buffer);

          // Write sensor index
          readAnswer(buffer, input2);
          writeData(sockfd, std::to_string(input2).c_str(), name);
        }
        // Read message
        readData(sockfd, buffer);
        printf("%s\n", buffer);
        break;
    } 
    std::cout << "0.Exit\n1. Get status\n2. Add new entity\n3. Remove entity\n\n";
    input = readNumberInInterval("Answer: ", 0, 3);
    std::cout << std::endl;
  }
  // Write end signal
  writeData(sockfd, "0", name);
  close(sockfd);
  return 0;
}
