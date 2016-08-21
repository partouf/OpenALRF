#include "ProxySensor.h"
#include <string>

OpenALRF::ProxySensor::ProxySensor(const string AIdentifier, const sensorid_t ASensorIDFilter) : ISensor(AIdentifier), ISensor3DBusListener(ASensorIDFilter)
{
   memset(&LatestValue, 0, sizeof(Sensor3DData));
}

std::string OpenALRF::ProxySensor::GetStatusInfo()
{
   return "";
}

void OpenALRF::ProxySensor::PowerOff()
{
}

void OpenALRF::ProxySensor::PowerOn()
{
}

bool OpenALRF::ProxySensor::IsPowered()
{
   return true;
}

OpenALRF::Sensor3DData OpenALRF::ProxySensor::NextValue()
{
   return LatestValue;
}

void OpenALRF::ProxySensor::NewSensorData(const SensorBusData3D ABusData)
{
   LatestValue = ABusData.Data;
}
