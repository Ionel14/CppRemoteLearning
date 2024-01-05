#include "smarthomestatus.h"

namespace smart_home
{
    void SmartHomeStatus::PrintSensorsStatus(std::vector<StatusObject*> &objects)
    {
        for (auto& object : objects)
        {
            std::cout<<object->Status()<<std::endl<<std::endl; 
        }
        
    }


} // namespace smart_home
