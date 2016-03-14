#pragma once

#include <string>

namespace OpenALRF
{
   class IModule
   {
   public:
      virtual std::string GetStatusInfo() = 0;
   };
};
