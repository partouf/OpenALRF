#include "ProxySensor.h"
#include <cstring>

OpenALRF::ProxySensor::ProxySensor(OpenALRF::sensorid_t AIdentifier) : ISensor(AIdentifier), ISensor3DBusListener(AIdentifier)
{
   Origin = sensoriRemote;
}

std::string OpenALRF::ProxySensor::GetStatusInfo()
{
   std::string info = ISensor::GetStatusInfo();

   return info;
}

void OpenALRF::ProxySensor::PowerOff()
{
}

void OpenALRF::ProxySensor::PowerOn()
{
}

bool OpenALRF::ProxySensor::IsPowered() const
{
   return true;
}

bool OpenALRF::ProxySensor::NextValue(OpenALRF::Sensor3DData &AValue)
{
   if (LatestSensorData.Timestamp != 0)
   {
      AValue = LatestSensorData;

      return true;
   }

   return false;
}

void OpenALRF::ProxySensor::NewSensorData(const SensorBusData3D ABusData)
{
   Type = ABusData.Type;
   UsedUnit = ABusData.UnitUsed;

   LatestSensorData = ABusData.Data;
}
