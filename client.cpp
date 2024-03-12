#include <iostream>
#include <netinet/in.h>
#include <netdb.h> 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>


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

void writeData(int sockfd, const char buffer[]) {
  if (write(sockfd, buffer, strlen(buffer)) < 0) {
    error("Error writing to socket");
  }
}

void readAnswer(char buffer[], int& input) {
  printf("%s\n", buffer);
  std::cout << "Answer: ";
  std::cin >> input;
  std::cout << std::endl;
}


int main(int argc, char *argv[]) {
  int sockfd, portno;
  struct sockaddr_in serv_addr;
  struct hostent *server;

  char buffer[512];
  std::string message;
  int input, input2;
  std::string inputStr, inputStr2;

  portno = argc == 2 ? atoi(argv[1]) : 3000;
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


  std::cout << "0.Exit\n1. Get status\n2. Add new entity\n3. Remove entity\n\nAnswer: ";
  std::cin >> input;
  std::cout << std::endl;
  bzero(buffer, 512);
  while (input != 0) {
    switch(input) {
      case 1: // Get status
        std::cout << "1. Sensor\n2. Device\n3. Room\n4. Home\n\nAnswer: ";
        std::cin >> input;
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
        writeData(sockfd, buffer);

        if (input == 1 || input == 2 || input == 3) {
          // Read rooms
          readData(sockfd, buffer);

          // Write room index
          readAnswer(buffer, input2);
          writeData(sockfd, std::to_string(input2).c_str());

          if (input == 1 || input == 2) {
            // Read devices
            readData(sockfd, buffer);

            // Write device index
            readAnswer(buffer, input2);
            writeData(sockfd, std::to_string(input2).c_str());

            if(input == 1) {
              // Read sensors
              readData(sockfd, buffer);

              // Write sensor index
              readAnswer(buffer, input2);
              writeData(sockfd, std::to_string(input2).c_str());
            }
          }
        }
        // Read status
        readData(sockfd, buffer);
        printf("%s\n", buffer);
        break;
      case 2: // Add new entity
        std::cout << "1. Sensor\n2. Device\n\nAnswer: ";
        std::cin >> input;
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
        writeData(sockfd, buffer);

        // Read rooms
        readData(sockfd, buffer);

        // Write room index
        readAnswer(buffer, input2);
        writeData(sockfd, std::to_string(input2).c_str());

        if (input == 1) {
          // Read devices
          readData(sockfd, buffer);

          // Write device index
          readAnswer(buffer, input2);
          writeData(sockfd, std::to_string(input2).c_str());

          // Read sensor types
          readData(sockfd, buffer);

          // Write sensor type
          readAnswer(buffer, input2);
          writeData(sockfd, std::to_string(input2).c_str());

          std::cout << "Sensor name: ";
          std::cin >> inputStr;
          std::cout << "Sensor value: ";
          std::cin >> inputStr2;
          std::cout << std::endl;

        } else {
          // Read device types
          readData(sockfd, buffer);

          // Write device type
          readAnswer(buffer, input2);
          writeData(sockfd, std::to_string(input2).c_str());

          std::cout << "Device name: ";
          std::cin >> inputStr;
          std::cout << "Device state (on/ off): ";
          std::cin >> inputStr2;
          std::cout << std::endl;
        }
        // Write name
        readData(sockfd, buffer);
        writeData(sockfd, inputStr.c_str());

        // Write value/ state
        readData(sockfd, buffer);
        writeData(sockfd, inputStr2.c_str());

        // Read message
        readData(sockfd, buffer);
        printf("%s\n", buffer);
        break;
      case 3: // Remove entity
        std::cout << "1. Sensor\n2. Device\n\nAnswer: ";
        std::cin >> input;
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
        writeData(sockfd, buffer);

        // Read rooms
        readData(sockfd, buffer);

        // Write room index
        readAnswer(buffer, input2);
        writeData(sockfd, std::to_string(input2).c_str());
        
        // Read devices
        readData(sockfd, buffer);

        // Write device index
        readAnswer(buffer, input2);
        writeData(sockfd, std::to_string(input2).c_str());

        if(input == 1) {
          // Read sensors
          readData(sockfd, buffer);

          // Write sensor index
          readAnswer(buffer, input2);
          writeData(sockfd, std::to_string(input2).c_str());
        }
        // Read message
        readData(sockfd, buffer);
        printf("%s\n", buffer);
        break;
    } 
    std::cout << "0.Exit\n1. Get status\n2. Add new entity\n3. Remove entity\n\nAnswer: ";
    std::cin >> input;
    std::cout << std::endl;
  }
  // Write end signal
  writeData(sockfd, "0");
  close(sockfd);
  return 0;
}
