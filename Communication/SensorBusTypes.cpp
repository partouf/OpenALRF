#include "SensorBusTypes.h"
#include <sstream>

std::ostream & OpenALRF::operator<<(std::ostream & stream, const SensorBusData3D & busdata)
{
   std::string streambuffer;
   streambuffer << busdata;
   stream << streambuffer;

   return stream;
}

std::string & OpenALRF::operator<<(std::string & stream, const SensorBusData3D & busdata)
{
   std::string streambuffer;
   streambuffer.reserve(37);

   char buffer[4];

   buffer[0] = 1;
   buffer[1] = busdata.ID;
   buffer[2] = static_cast<char>(busdata.Type);
   buffer[3] = static_cast<char>(busdata.UnitUsed);

   streambuffer.append(buffer, 4);

   streambuffer << busdata.Data;

   buffer[0] = 23;
   streambuffer.append(buffer, 1);

   stream.append(streambuffer);

   return stream;
}
