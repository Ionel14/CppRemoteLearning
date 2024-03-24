#ifndef NAGARROREMOTELEARNINGSERVER_SERVERUTILS_H
#define NAGARROREMOTELEARNINGSERVER_SERVERUTILS_H

enum class RequestType {
    GetDevicesStatus,
    AddDevice,
    RemoveDevice,
    GetDeviceStatus,
    GetHouseSensorStatus,
    GetRoomSensorStatus,
    GetSensorStatus,
    AddSensorToRoom,
    RemoveSensorFromRoom,
    InvalidRequest
};

const char* welcomeMessage = "Welcome to the Smart Home Server!\n"
                             "Available commands:\n"
                             "1. getDevicesStatus - Retrieves the status of all devices.\n"
                             "2. addDevice,<deviceType> - Adds a new device of the specified type.\n"
                             "3. removeDevice,<deviceType> - Removes a device of the specified type.\n"
                             "4. getDeviceStatus,<deviceType> - Gets the status of a specific device type.\n"
                             "5. getHouseSensorStatus - Retrieves the status of all sensors in the house.\n"
                             "6. getRoomSensorStatus,<roomType> - Retrieves the status of all sensors in a specific room.\n"
                             "7. getSensorStatus,<roomType>,<sensorName> - Gets the status of a specific sensor in a room.\n"
                             "8. addSensorToRoom,<roomType>,<sensorName> - Adds a sensor to a specific room.\n"
                             "9. removeSensorFromRoom,<roomType>,<sensorName> - Removes a sensor from a specific room.\n"
                             "Please use the commands exactly as shown, with parameters separated by commas.\n"
                             "<deviceType> can be 0 for light, 1 for heater or 2 for airConditioner.\n"
                             "<roomType> can be 0 for livingRoom, 1 for bedroom or 2 for kitchen.\n"
                             "<sensorName> can be TempSensor, HumiditySensor or MonoxideSensor.\n"
                             "Type 'exit' to close the connection.\n";

bool isDeviceRequest(RequestType requestType) {
    return requestType == RequestType::AddDevice || requestType == RequestType::RemoveDevice ||
           requestType == RequestType::GetDeviceStatus || requestType == RequestType::GetDevicesStatus;
}

bool isSensorRequest(RequestType requestType) {
    return requestType == RequestType::GetHouseSensorStatus || requestType == RequestType::GetRoomSensorStatus ||
           requestType == RequestType::GetSensorStatus || requestType == RequestType::AddSensorToRoom ||
           requestType == RequestType::RemoveSensorFromRoom;
}

RequestType determineRequestType(const std::string& request) {
    if (request == "getDevicesStatus") {
        return RequestType::GetDevicesStatus;
    } else if (request.find("addDevice") != std::string::npos) {
        return RequestType::AddDevice;
    } else if (request.find("removeDevice") != std::string::npos) {
        return RequestType::RemoveDevice;
    } else if (request.find("getDeviceStatus") != std::string::npos) {
        return RequestType::GetDeviceStatus;
    } else if (request.find("getHouseSensorStatus") != std::string::npos) {
        return RequestType::GetHouseSensorStatus;
    } else if (request.find("getRoomSensorStatus") != std::string::npos) {
        return RequestType::GetRoomSensorStatus;
    } else if (request.find("getSensorStatus") != std::string::npos) {
        return RequestType::GetSensorStatus;
    } else if (request.find("addSensorToRoom") != std::string::npos) {
        return RequestType::AddSensorToRoom;
    } else if (request.find("removeSensorFromRoom") != std::string::npos) {
        return RequestType::RemoveSensorFromRoom;
    } else {
        return RequestType::InvalidRequest;
    }
}

#endif
