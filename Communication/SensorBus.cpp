#include "SensorBus.h"

void OpenALRF::SensorBus::Broadcast(const sensorid_t AID, const sensor_t ASensorType, const sensorunit_t AUnitUsed, const Sensor3DData ASensorData)
{
   SensorBusData3D Data;
   Data.ID = AID;
   Data.Type = ASensorType;
   Data.Data = ASensorData;
   Data.UnitUsed = AUnitUsed;

   Broadcast(Data);
}

void OpenALRF::SensorBus::Broadcast(const SensorBusData3D ABusSensorData)
{
   for (auto Listener : SubscriberInstances)
   {
      if (Listener != nullptr)
      {
         auto filter = Listener->GetIDFilter();
         if ((filter == ABusSensorData.ID) || (filter == ALLSENSORS))
         {
            Listener->NewSensorData(ABusSensorData);
         }
      }
   }
}

std::string OpenALRF::SensorBus::GetStatusInfo()
{
   std::string listeners;

   for (auto Listener : SubscriberInstances)
   {
      sensorid_t filter = Listener->GetIDFilter();
      char filterstr[1024];
      sprintf(filterstr, "%d", filter);

      listeners += "<listener filter='";
      listeners += filterstr;
      listeners += "' />";
   }

   return listeners;
}

OpenALRF::SensorBus::SensorBus() : IModule()
{
}

void OpenALRF::SensorBus::Subscribe(ISensor3DBusListener *AListener)
{
   SubscriberInstances.push_back(AListener);
}

void OpenALRF::SensorBus::ClearSubscribers()
{
   SubscriberInstances.clear();
}
