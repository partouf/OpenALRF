#pragma once

#include "SensorBusTypes.h"
#include "../Sensors/Sensors.h"

namespace OpenALRF
{
   class ISensor3DBusListener: public ISensor
   {
   protected:
      sensorid_t SensorIDFilter;
   public:
      ISensor3DBusListener(const OpenALRF::sensorid_t ASensorIDFilter);

      OpenALRF::sensorid_t GetIDFilter() const;

      virtual void NewSensorData(const OpenALRF::SensorBusData3D ABusData) = 0;
   };
};
