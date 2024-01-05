#ifndef SMART_HOME_SERVICES_TEMPERATURE_SERVICE_H_
#define SMART_HOME_SERVICES_TEMPERATURE_SERVICE_H_

#include "service.h"

namespace services {

// Rule of Zero

class TemperatureService : public Service {
  public:
    void Refresh() override;
};

}

#endif // SMART_HOME_SERVICES_TEMPERATURE_SERVICE_H_