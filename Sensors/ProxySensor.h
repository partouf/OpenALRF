#pragma once

#include "Sensors.h"
#include "../Communication/SensorBusListener.h"

namespace OpenALRF
{
   class ProxySensor : public ISensor3DBusListener
   {
   public:
      ProxySensor(OpenALRF::sensorid_t AIdentifier);


      // Inherited via ISensor
      virtual void PowerOff() override;

      virtual void PowerOn() override;

      virtual bool IsPowered() const override;

      virtual bool NextValue(OpenALRF::Sensor3DData & AValue) override;


      // Inherited via ISensor3DBusListener
      virtual void NewSensorData(const SensorBusData3D ABusData) override;

   };
};
