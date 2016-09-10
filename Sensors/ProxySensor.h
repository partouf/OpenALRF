#pragma once

#include "Sensors.h"
#include "../Communication/SensorBusListener.h"

namespace OpenALRF
{
   // note: #panic we're inheriting from 2 classes, should rewrite

   class ProxySensor : public ISensor, ISensor3DBusListener
   {
   public:
      ProxySensor(OpenALRF::sensorid_t AIdentifier);

      virtual std::string GetStatusInfo() override;

      virtual void PowerOff() override;

      virtual void PowerOn() override;

      virtual bool IsPowered() const override;

      virtual bool NextValue(OpenALRF::Sensor3DData &AValue) override;


      // Inherited via ISensor3DBusListener
      void NewSensorData(const SensorBusData3D ABusData) override;
   };
};
