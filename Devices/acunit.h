#ifndef ACUNIT_H
#define ACUNIT_H

#include "device.h"
#include "acmode.h"

namespace smart_home
{

class AcUnit : public Device
{
public:
    AcUnit(const std::string &name = "", DeviceStatus status = DeviceStatus::kOff, AcMode mode = AcMode::kCold);
    AcMode GetMode();
    void SwitchMode();
    const std::string Status() override;
private:
    AcMode mode_;
};

} // namespace smart_home

#endif