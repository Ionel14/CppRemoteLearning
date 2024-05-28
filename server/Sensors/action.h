#ifndef ACTION_H
#define ACTION_H

namespace smart_home
{

enum class Action{
    kNone = 0,
    kLowerTheTemperature,
    kRaiseTheTemperature,
    kNeedMoreLight,
    kTooMuchHumidity,
    kIsAPresence
};

} // namespace smart_home

#endif