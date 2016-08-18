#pragma once

#include "Types.h"

namespace OpenALRF
{
   timestamp_t GetCurrentTimestamp();
   std::string GetTimestampAsString(OpenALRF::timestamp_t ATimestamp);
};
