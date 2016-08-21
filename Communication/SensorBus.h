#pragma once

#include <string>
#include <vector>
#include "../System/Module.h"
#include "../Sensors/SensorTypes.h"
#include "SensorBusTypes.h"
#include "SensorBusListener.h"

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

      std::string GetStatusInfo() override;
   };
};
