#pragma once

#include "../System/Module.h"
#include "../Common/Types.h"
#include "SensorTypes.h"

namespace OpenALRF
{
   class ISensor : public IModule
   {
   protected:
      sensorid_t Identifier;
      sensorunit_t UsedUnit;
      sensor_t Type;

      Sensor3DData LatestSensorData;
      
   public:
      ISensor(sensorid_t AIdentifier);

      virtual sensorid_t GetIdentifier();

      virtual sensorunit_t GetUsedUnit();
      virtual sensor_t GetSensorType();

      virtual void PowerOff() = 0;
      virtual void PowerOn() = 0;
      virtual bool IsPowered() = 0;

      virtual bool NextValue(OpenALRF::Sensor3DData &AValue) = 0;

      // Inherited via IModule
      virtual std::string GetStatusInfo() override;
   };

   std::string Sensor3DDataAsXML(const OpenALRF::Sensor3DData AValue);
};
