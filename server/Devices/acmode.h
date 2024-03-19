#ifndef ACMODE_H
#define ACMODE_H

namespace smart_home
{

enum class AcMode{
    kHeat = 0,
    kCold,
    kUndefined,
};

inline const char* AcModeToString(AcMode v)
{
    switch (v)
    {
        case (smart_home::AcMode::kCold):   return "Cold";
        case (smart_home::AcMode::kHeat):   return "Heat";
        default:    return "[Unknown type]";
    }
}

inline AcMode StringToAcMode(const char* v)
{
        if (v == "Cold")   return smart_home::AcMode::kCold;
        if (v == "Heat")   return smart_home::AcMode::kHeat;
        return smart_home::AcMode::kUndefined;
}

} // namespace smart_home

#endif