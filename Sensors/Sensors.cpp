#include "Sensors.h"

OpenALRF::ISensor::ISensor(const std::string AIdentifier) : IModule()
{
   Identifier = AIdentifier;
}

std::string OpenALRF::ISensor::GetIdentifier()
{
   return Identifier;
}
