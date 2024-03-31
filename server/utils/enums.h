#ifndef NAGARROREMOTELEARNING_ENUMS_H
#define NAGARROREMOTELEARNING_ENUMS_H

enum MeasureUnit {
    CELSIUS,
    PERCENT,
    UNKNOWN,
};

enum RoomType {
    LIVING_ROOM,
    BEDROOM,
    KITCHEN,
    UNKNOWN_ROOM,
};

enum DeviceType {
    LIGHT,
    HEATER,
    AIR_CONDITIONER,
    UNKNOWN_DEVICE,
};

enum SensorType {
    TEMPERATURE,
    HUMIDITY,
    MONOXIDE,
    UNKNOWN_SENSOR,
};

const int ROOM_NUM = 3;

static RoomType getRoomTypeFromInt(int roomType){
    switch (roomType) {
        case 0:
            return LIVING_ROOM;
        case 1:
            return BEDROOM;
        case 2:
            return KITCHEN;
        default:
            return UNKNOWN_ROOM;
    }
}

static std::string getSensorTypeString(SensorType sensorType){
    switch (sensorType) {
        case TEMPERATURE:
            return "TempSensor";
        case HUMIDITY:
            return "HumiditySensor";
        case MONOXIDE:
            return "MonoxideSensor";
        default:
            return "ERROR";
    }
}

static SensorType parseSensorTypeFromSensorName(const std::string& sensorName){
    if (sensorName.find("TempSensor") != std::string::npos){
        return TEMPERATURE;
    } else if (sensorName.find("HumiditySensor") != std::string::npos){
        return HUMIDITY;
    } else if (sensorName.find("MonoxideSensor") != std::string::npos){
        return MONOXIDE;
    } else {
        return UNKNOWN_SENSOR;
    }
}

static SensorType getSensorTypeFromString(const std::string& sensorType){
    if (sensorType == "TempSensor"){
        return TEMPERATURE;
    } else if (sensorType == "HumiditySensor"){
        return HUMIDITY;
    } else if (sensorType == "MonoxideSensor"){
        return MONOXIDE;
    } else {
        return UNKNOWN_SENSOR;
    }
}

static std::string getDeviceTypeString(DeviceType deviceType){
    switch (deviceType) {
        case LIGHT:
            return "Light";
        case HEATER:
            return "Heater";
        case AIR_CONDITIONER:
            return "Air Conditioner";
        default:
            return "ERROR";
    }
}

#endif
