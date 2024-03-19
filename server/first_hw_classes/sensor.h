#ifndef SENSOR_H
#define SENSOR_H

#include <string>

namespace smart_home
{

class Sensor
{
public:
    Sensor(const std::string &name = "", const std::string &type = "", float value = 0);
    std::string& GetName();
    void SetName(const std::string &name);

    std::string& GetType(); 
    void SetType(const std::string &type);

    float GetValue();
    void SetValue(float value);

private:
    std::string name_;
    std::string type_;
    float value_;
};

} // namespace smart_home

#endif