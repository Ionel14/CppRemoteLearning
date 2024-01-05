#include <iostream>
#include "services/light_service.h"

namespace services {

void LightService::Refresh() {
    std::cout << "Light service refreshing..." << std::endl;
    Service::SetDevicesOnAuto();
}

} // namespace services

