# Nagarro Remote Learning | Homework 5

In this README, I will briefly explain the logic of the classes, as well as some technical decisions taken for creating this smart home project.

# Folder Structure
1. Devices 
2. Sensors 
3. House 
4. User 
5. Utils 

## Devices
The `Devices` folder contains classes and functionality related to the various devices in the smart home. This includes devices like lights, heaters, air conditioners, and any other controllable or interactive hardware. These classes typically include methods for controlling the device state, such as turning a device on or off, adjusting settings, etc.

## Sensors
The `Sensors` folder is dedicated to sensor-related classes. Sensors could include temperature sensors, humidity sensors, monoxide sensors, and other types of environmental sensors. These classes are responsible for reading and processing sensor data, which can then be used for monitoring the environment or triggering certain actions in the smart home system.

## House
The `House` folder encompasses classes that represent the physical structure of the smart home, such as rooms and the house itself. It typically includes the logic for managing the various components of a house, like rooms, their associated sensors and devices, and overall house-level operations.

## User
The `User` folder contains classes related to user interaction with the smart home system. This can include user profiles, preferences, and user-specific functionalities like custom settings for devices or sensors. It's where the logic for user authentication, personalization, and user-specific controls would reside.

## Utils
The `Utils` (Utilities) folder is used for miscellaneous helper classes, functions, and resources that are used across the project. This might include utility functions for data formatting, common operations, and other helper methods that don't fit into the specific categories of devices, sensors, house, or user.

# SOLID Principles in Smart Home Project

## Single Responsibility Principle (SRP)

- **Application**: Each folder in the project (Devices, Sensors, House, User, Utils) encapsulates a specific aspect of the smart home system.
- **Benefit**: Changes in one aspect (like sensor functionality) have minimal impact on other aspects, adhering to the principle that a class should have only one reason to change.

## Open/Closed Principle (OCP)

- **Application**: Base classes in the `House` and `Sensors` folders are designed to be extended (for different types of rooms or sensors) without modifying existing code.
- **Benefit**: This approach allows for the addition of new features and functionalities with minimal changes to existing code.

## Liskov Substitution Principle (LSP)

- **Application**: Subclasses in the `Devices` folder (like `Light` and `Heater`) are designed to be used interchangeably through their base `Device` class interface.
- **Benefit**: Ensures that replacing a superclass object with a subclass object does not affect the correctness of the program.

## Interface Segregation Principle (ISP)

- **Application**: Creation of small, specific interfaces for device and sensor interactions rather than large, general-purpose ones.
- **Benefit**: Reduces the burden on implementing classes by ensuring they only need to concern themselves with the methods they actually use.

## Dependency Inversion Principle (DIP)

- **Application**: Classes in the `User` folder that manage interactions with devices and sensors depend on abstract interfaces, not concrete implementations.
- **Benefit**: Increases modularity and flexibility, making the system easier to test and adapt to changes, such as the introduction of new device types.

