#pragma once

#include "../Sensors/SensorTypes.h"
#include "../Sensors/Sensors.h"
#include <cstdint>

namespace OpenALRF
{
#define ALLSENSORS 0

   struct SensorConfig
   {
      sensorid_t ID;
      std::string IPAddress;
   };

   struct SensorBusData3D
   {
      sensororigin_t Origin;
      sensor_t Type;
      sensorid_t ID;
      sensorunit_t UnitUsed;
      Sensor3DData Data;
   };
   std::ostream &operator<<(std::ostream &stream, const SensorBusData3D &busdata);
   std::string &operator<<(std::string &stream, const SensorBusData3D &busdata);
}; // namespace OpenALRF
