#pragma once

#include <cstdint>
#include "../Common/Types.h"

namespace OpenALRF
{
   typedef int8_t sensorid_t;

   enum sensororigin_t
   {
      sensoriLocal = 0,
      sensoriRemote = 1
   };

   struct Sensor3DData
   {
      timestamp_t Timestamp;
      double Data1;
      double Data2;
      double Data3;
   };
   std::ostream& operator<< (std::ostream& stream, const Sensor3DData& sensordata);
   std::string& operator<< (std::string& stream, const Sensor3DData& sensordata);

   struct OrientationPRY
   {
      double Pitch;
      double Roll;
      double Yaw;
   };

   struct Orientation3D
   {
      double X;
      double Y;
      double Z;
   };

   enum sensor_t
   {
      sensorUnknown = 0,

      sensorUltrasonic = 10,

      sensorWheelEncoder = 20,

      sensorHumidity = 30,
      sensorTemperature = 31,
      sensorPressure = 32,

      sensorGyroscope = 40,
      sensorAccelerometer = 41,

      sensorMagnetometer = 50
   };

   enum sensorunit_t
   {
      unitUnknown = 0,
      unitPercentage = 1,

      unitCelcius = 20,

      unitDegrees = 30,

      unitMeters = 40,

      unitMetersPerSecond = 50,
      unitG = 55,

      unitMicroTesla = 60,

      unitPascal = 70,

      unitTicks = 80
   };
};
