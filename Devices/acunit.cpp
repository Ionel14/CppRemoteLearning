#include "acunit.h"

namespace smart_home
{

AcUnit::AcUnit(const std::string &name, DeviceStatus status, AcMode mode): Device(name, status), mode_{mode}{}

AcMode AcUnit::GetMode()
{
    return mode_;
}

void AcUnit::SwitchMode()
{
    if (mode_ == AcMode::kCold)
    {
        mode_ = AcMode::kHeat;
        return;
    }

    mode_ = AcMode::kCold;
}

const std::string AcUnit::Status()
{
    std::string status = GetName() + ": " + DeviceStatusToString(GetStatus()) + "\nMode-";
    if (mode_ == AcMode::kCold)
    {
        status+= "Cold";
    }
    else
    {
        status+= "Heat";
    }

    return status;
}

} // namespace smart_home