#include "ProxySensorWithHistory.h"

OpenALRF::ProxySensorWithHistory::ProxySensorWithHistory(OpenALRF::sensorid_t AIdentifier) : ProxySensor(AIdentifier)
{
   maxsize = 1000;
   history.reserve(maxsize);
}

void OpenALRF::ProxySensorWithHistory::NewSensorData(const SensorBusData3D ABusData)
{
   history.push_back(ABusData);
   if (history.size() >= maxsize)
   {
      history.erase(history.begin());
   }

   OpenALRF::ProxySensor::NewSensorData(ABusData);
}
