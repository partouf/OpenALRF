#include "Sensors.h"
#include "../Common/Timing.h"
#include <cstring>
#include <sstream>
#include <locale>

OpenALRF::ISensor::ISensor(OpenALRF::sensorid_t AIdentifier) : IModule()
{
   Identifier = AIdentifier;
   Type = sensorUnknown;
   UsedUnit = unitUnknown;
   Origin = sensoriLocal;
   memset(&LatestSensorData, 0, sizeof(Sensor3DData));
}

OpenALRF::sensorunit_t OpenALRF::ISensor::GetUsedUnit() const
{
   return UsedUnit;
}

OpenALRF::sensor_t OpenALRF::ISensor::GetSensorType() const
{
   return Type;
}

OpenALRF::sensororigin_t OpenALRF::ISensor::GetOrigin() const
{
   return Origin;
}

std::string OpenALRF::ISensor::GetStatusInfo() const
{
   std::string info;

   char val[1024];

   sprintf(val, "<ID>%d</ID>", Identifier);
   info += val;

   sprintf(val, "<Type>%d</Type>", Type);
   info += val;

   sprintf(val, "<UsedUnit>%d</UsedUnit>", UsedUnit);
   info += val;

   if (LatestSensorData.Timestamp != 0)
   {
      info += "<LatestSensorData>";
      info += Sensor3DDataAsXML(LatestSensorData);
      info += "</LatestSensorData>";
   }
   else
   {
      info += "<LatestSensorData />";
   }

   return info;
}

OpenALRF::sensorid_t OpenALRF::ISensor::GetIdentifier() const
{
   return Identifier;
}

std::string OpenALRF::Sensor3DDataAsXML(const OpenALRF::Sensor3DData AValue)
{
   std::string xml;

   std::ostringstream ostr;
   ostr.imbue(std::locale("C"));

   char data[1024] = "";

   auto timestampstr = GetTimestampAsString(AValue.Timestamp);
   timestampstr = timestampstr.replace(timestampstr.find(' '), 1, "T");

   sprintf(data, "<Timestamp>%s</Timestamp>", timestampstr.c_str());
   xml += data;

   float tmp;

   tmp = AValue.Data1;
   ostr << "<Data1>" << tmp << "</Data1>";

   tmp = AValue.Data2;
   ostr << "<Data2>" << tmp << "</Data2>";

   tmp = AValue.Data3;
   ostr << "<Data3>" << tmp << "</Data3>";

   return xml + ostr.str();
}
