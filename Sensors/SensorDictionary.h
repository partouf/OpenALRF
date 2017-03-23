#pragma once

#include "SensorTypes.h"

namespace OpenALRF
{
   class SensorDictionary
   {
   public:
      static std::string GetSensorName(sensor_t ASensorID);
      static std::string GetUnitSymbol(sensorunit_t ASensorUnit);

      static OpenALRF::sensor_t GetSensorTypeFromName(const std::string AType);
   };
}
