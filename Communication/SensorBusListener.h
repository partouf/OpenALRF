#pragma once

#include "SensorBusTypes.h"

namespace OpenALRF
{
   class ISensor3DBusListener
   {
   protected:
      sensorid_t SensorIDFilter;
   public:
      ISensor3DBusListener(const sensorid_t ASensorIDFilter);

      sensorid_t GetIDFilter() const;

      virtual void NewSensorData(const SensorBusData3D ABusData) = 0;
   };
};
