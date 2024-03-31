#include "serverUtils.h"
#include <unordered_set>

std::vector<std::string> splitString(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

RoomType parseRoomType(const std::string& roomTypeStr) {
    if (roomTypeStr == "0") return RoomType::LIVING_ROOM;
    else if (roomTypeStr == "1") return RoomType::BEDROOM;
    else if (roomTypeStr == "2") return RoomType::KITCHEN;
    else return RoomType::UNKNOWN_ROOM;
}

DeviceType parseDeviceType(const std::string& deviceTypeStr) {
    if (deviceTypeStr == "0") return DeviceType::LIGHT;
    else if (deviceTypeStr == "1") return DeviceType::HEATER;
    else if (deviceTypeStr == "2") return DeviceType::AIR_CONDITIONER;
    else return DeviceType::UNKNOWN_DEVICE;
}

std::string executeDeviceAction(smart_home::User& user, RequestType requestType, int deviceType) {
    try {
        switch (requestType) {
            case RequestType::AddDevice:
                user.addDevice(static_cast<DeviceType>(deviceType));
                return "Device added.";
            case RequestType::RemoveDevice:
                user.removeDevice(static_cast<DeviceType>(deviceType));
                return "Device removed.";
            case RequestType::GetDeviceStatus:
                return user.getDeviceStatus(static_cast<DeviceType>(deviceType));
            default:
                return "Invalid device action.";
        }
    } catch (std::exception& e) {
        return std::string("Error processing device request: ") + e.what();
    }
}

std::string handleDeviceRequest(smart_home::User& user, RequestType requestType, const std::string& request) {
    if (requestType == RequestType::GetDevicesStatus) {
        return user.getDevicesStatus();
    }

    if (requestType == RequestType::AddDevice || requestType == RequestType::RemoveDevice || requestType == RequestType::GetDeviceStatus) {
        size_t commaPos = request.find(",");
        if (commaPos == std::string::npos) {
            return "Invalid format for request.";
        }

        std::string deviceTypeStr = request.substr(commaPos + 1);
        DeviceType deviceType = parseDeviceType(deviceTypeStr);
        if (deviceType == DeviceType::UNKNOWN_DEVICE) {
            return "Invalid device type.";
        }
        return executeDeviceAction(user, requestType, deviceType);
    }

    return "Invalid device request.";
}

std::string handleSensorRequest(smart_home::User& user, RequestType requestType, const std::vector<std::string>& tokens) {
    std::string response;

    if (requestType == RequestType::GetHouseSensorStatus) {
        response = user.getHouseSensorStatus();
    } else if (requestType == RequestType::GetRoomSensorStatus && tokens.size() >= 2) {
        RoomType roomType = parseRoomType(tokens[1]);
        response = user.getRoomSensorStatus(roomType);
    } else if (requestType == RequestType::GetSensorStatus && tokens.size() >= 3) {
        RoomType roomType = parseRoomType(tokens[1]);
        const std::string& sensorName = tokens[2];
        response = user.getSensorStatus(roomType, sensorName);
    } else if (requestType == RequestType::AddSensorToRoom && tokens.size() >= 3) {
        RoomType roomType = parseRoomType(tokens[1]);
        const std::string& sensorName = tokens[2];
        user.addSensorToRoom(roomType, sensorName);
        response = "Sensor added to room.";
    } else if (requestType == RequestType::RemoveSensorFromRoom && tokens.size() >= 3) {
        RoomType roomType = parseRoomType(tokens[1]);
        const std::string& sensorName = tokens[2];
        user.removeSensorFromRoom(roomType, sensorName);
        response = "Sensor removed from room.";
    } else {
        response = "Invalid sensor request.";
    }

    return response;
}

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
    static const std::unordered_set<RequestType> deviceRequests = {
            RequestType::AddDevice,
            RequestType::RemoveDevice,
            RequestType::GetDeviceStatus,
            RequestType::GetDevicesStatus
    };

    return deviceRequests.find(requestType) != deviceRequests.end();
}

bool isSensorRequest(RequestType requestType) {
    static const std::unordered_set<RequestType> sensorRequests = {
            RequestType::GetHouseSensorStatus,
            RequestType::GetRoomSensorStatus,
            RequestType::GetSensorStatus,
            RequestType::AddSensorToRoom,
            RequestType::RemoveSensorFromRoom
    };

    return sensorRequests.find(requestType) != sensorRequests.end();
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
