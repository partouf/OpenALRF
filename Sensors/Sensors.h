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
      sensororigin_t Origin;

      Sensor3DData LatestSensorData;
      
   public:
      ISensor(sensorid_t AIdentifier);

      virtual sensorid_t GetIdentifier() const;

      virtual sensorunit_t GetUsedUnit() const;
      virtual sensor_t GetSensorType() const;
      virtual sensororigin_t GetOrigin() const;

      virtual void PowerOff() = 0;
      virtual void PowerOn() = 0;
      virtual bool IsPowered() const = 0;

      virtual bool NextValue(OpenALRF::Sensor3DData &AValue) = 0;

      virtual Sensor3DData LatestValue() const;

      // Inherited via IModule
      virtual std::string GetStatusInfo() const override;
   };

   std::string Sensor3DDataAsXML(const OpenALRF::Sensor3DData AValue);
};
