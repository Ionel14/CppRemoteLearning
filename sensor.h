#ifndef SENSOR_H
#define SENSOR_H

#include <string>

class Sensor {
public:
    Sensor(const std::string& type, const std::string& sensorId, double value, bool isFunctional);

    const std::string getType() const;
    const std::string getID() const;
    double getValue() const;
    bool getIsFunctional() const;

private:
    std::string type;
    std::string sensorId;
    double value;
    bool isFunctional;
};

#endif // SENSOR_H