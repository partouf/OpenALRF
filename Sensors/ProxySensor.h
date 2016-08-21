#pragma once

#include "Sensors.h"
#include "../Communication/SensorBusListener.h"

namespace OpenALRF
{
   // note: #panic we're inheriting from 2 classes, should rewrite

   class ProxySensor : public ISensor, ISensor3DBusListener
   {
   protected:
      Sensor3DData LatestValue;

   public:
      ProxySensor(const string AIdentifier, const sensorid_t ASensorIDFilter);

      // Inherited via ISensor
      std::string GetStatusInfo() override;

      void PowerOff() override;

      void PowerOn() override;

      bool IsPowered() override;

      Sensor3DData NextValue() override;


      // Inherited via ISensor3DBusListener
      void NewSensorData(const SensorBusData3D ABusData) override;
   };
};
