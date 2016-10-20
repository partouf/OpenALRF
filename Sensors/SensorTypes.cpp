#include "SensorTypes.h"
#include "../Common/MemUtils.h"

std::ostream & OpenALRF::operator<<(std::ostream & stream, const Sensor3DData & sensordata)
{
   std::string streambuffer;

   streambuffer << sensordata;
   stream << streambuffer;

   return stream;
}

std::string & OpenALRF::operator<<(std::string & stream, const Sensor3DData & sensordata)
{
   char data[32];

   CopyMem<OpenALRF::timestamp_t>(&sensordata.Timestamp, data);
   CopyMem<double>(&sensordata.Data1, data + 8);
   CopyMem<double>(&sensordata.Data2, data + 16);
   CopyMem<double>(&sensordata.Data3, data + 24);

   stream.append(data, 32);

   return stream;
}
