#include <iostream>
#include "services/temperature_service.h"

namespace services {

void TemperatureService::Refresh() {
    std::cout << "Temperature service refreshing..." << std::endl;
    Service::SetDevicesOnAuto();
}

} // namespace services

