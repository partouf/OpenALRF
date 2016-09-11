#include "SensorBusListener.h"

OpenALRF::ISensor3DBusListener::ISensor3DBusListener(sensorid_t ASensorIDFilter) : ISensor::ISensor(ASensorIDFilter)
{
   SensorIDFilter = ASensorIDFilter;
}

OpenALRF::sensorid_t OpenALRF::ISensor3DBusListener::GetIDFilter() const
{
   return SensorIDFilter;
}
