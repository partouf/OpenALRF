#pragma once

#include <cstdint>
#include "../Sensors/Sensors.h"

namespace OpenALRF
{
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

      unitMicroTesla = 60
   };
};
