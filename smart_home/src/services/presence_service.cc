#include <iostream>
#include "services/presence_service.h"

namespace services {

void PresenceService::Refresh() {
    std::cout << "Presence service refreshing..." << std::endl;
    Service::SetDevicesOnAuto();
}

} // namespace services

