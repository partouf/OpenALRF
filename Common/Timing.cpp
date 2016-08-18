#include "Timing.h"

#include <ctime>

OpenALRF::timestamp_t OpenALRF::GetCurrentTimestamp()
{
   time_t tCurrent;

   time(&tCurrent);

   return tCurrent;
}

std::string OpenALRF::GetTimestampAsString(OpenALRF::timestamp_t ATimestamp)
{
   std::string format = "%Y-%m-%d %H:%M:%S";

   int maxlength = format.length() * 2 + 4;
   char *datetimestr = new char[maxlength];

   time_t ts = ATimestamp;
   struct tm *timeinfo = localtime(&ts);

   int len = strftime(datetimestr, maxlength, format.c_str(), timeinfo);
   datetimestr[len] = 0;

   return std::string(datetimestr);
}
