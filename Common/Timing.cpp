#include "Timing.h"

#include <ctime>

OpenALRF::timestamp_t OpenALRF::GetCurrentTimestamp()
{
   time_t tCurrent;

   time(&tCurrent);

   return tCurrent;
}
