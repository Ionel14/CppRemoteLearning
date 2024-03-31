#ifndef NAGARROREMOTELEARNINGSERVER_SERVERUTILS_H
#define NAGARROREMOTELEARNINGSERVER_SERVERUTILS_H
#include <string>
#include <vector>
#include <sstream>
#include "../user/User.h"


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

bool isDeviceRequest(RequestType requestType);
bool isSensorRequest(RequestType requestType);
RequestType determineRequestType(const std::string& request);
extern const char* welcomeMessage;


std::vector<std::string> splitString(const std::string& str, char delimiter);
RoomType parseRoomType(const std::string& roomTypeStr);
DeviceType parseDeviceType(const std::string& deviceTypeStr);
std::string handleDeviceRequest(smart_home::User& user, RequestType requestType, const std::string& request);
std::string handleSensorRequest(smart_home::User& user, RequestType requestType, const std::vector<std::string>& tokens);

#endif
