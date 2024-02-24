#ifndef DEVICE_H
#define DEVICE_H

#include <string>
namespace smart_home {

class Device
{
public:
    Device(const std::string &name = "", const std::string &type = "", bool status = false);

    std::string& GetName();
    void SetName(const std::string &name);

    std::string& GetType();
    void SetType(const std::string &type);

    bool GetStatus();
    void SetStatus(bool status);

private:
    std::string name_;
    std::string type_;
    bool status_;
};

}
#endif