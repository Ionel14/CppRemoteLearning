# Nagarro Remote Learning | Homework 4

In this README, I will briefly explain the logic of the classes, as well as some technical decisions taken for creating this smart home project.

## File Structure
1. main.cpp: the purpose of this file is to demonstrate the functionality of the classes.
2. User.h: the purpose of the user class is to act like a controller and interact with the devices present in the house. 
3. House.h: House is responasible for writing data to the file that the user will read from. 
4. Room.h: the class is repsonsible for storing sensors and to read the values from the sensors. 
5. Sensor.h: this class generates random values, representing sensor data.
6. Device.h: as the user can also control devices, these devices can have the states on or off.
7. enums.h: to better structure the code.

## Technical Decisions
User.h & Room.h: 
* Vector STL:  for devices and sensors, as the user could remove or add devices and sensors in his house, justifying the need of dynamic allocation.
* Inheritance: in User.h, I used a 'Has-A' type of inheritance, as one user has a userHouse.

House.h:
* Array Data Type: the number of rooms in a house is constant, so a simple, static array is the best choice. 

Sensor.h:
* Rule of 5: in this class, I demonstranted the use of rule-of-5.

enums.h:
* enums: used for better code legibility.