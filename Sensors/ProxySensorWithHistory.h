#pragma once

#include "ProxySensor.h"
#include <vector>

namespace OpenALRF
{
   class ProxySensorWithHistory : public ProxySensor
   {
   protected:
      std::vector<SensorBusData3D> history;
      size_t maxsize;
   public:
      ProxySensorWithHistory(OpenALRF::sensorid_t AIdentifier);

      virtual void NewSensorData(const SensorBusData3D ABusData) override;
   };
}
