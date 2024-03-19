#include <vector>

#include "smarthomemanager.h"

int main()
{
    
    smart_home::SmartHome smartHome;
    smart_home::SmartHomeManager smartHomeMgr(smartHome);

    smartHomeMgr.StartServer();
    
    return 0;
}