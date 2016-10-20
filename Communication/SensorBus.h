#pragma once

#include "../Sensors/SensorTypes.h"
#include "../System/Module.h"
#include "SensorBusListener.h"
#include "SensorBusTypes.h"
#include <string>
#include <vector>

using namespace std;

namespace OpenALRF
{
   class SensorBus : public IModule
   {
   protected:
      vector<ISensor3DBusListener *> SubscriberInstances;

   public:
      SensorBus();

      void Subscribe(ISensor3DBusListener *AListener);
      void ClearSubscribers();

      void Broadcast(const sensorid_t AID, const sensor_t ASensorType, const sensorunit_t AUnitUsed, const Sensor3DData ASensorData);
      void Broadcast(const SensorBusData3D ABusSensorData);

      std::string GetStatusInfo() const override;
   };
};
