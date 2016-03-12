#pragma once

#include <string>

namespace OpenALRF
{
   class ISystem
   {
   public:
      virtual void RebootNow() = 0;

      virtual bool HasValidActiveNetwork() = 0;

      virtual void RestartNetworkInterface(const std::string AInterfaceName) = 0;

      virtual bool ShouldQuit() = 0;
   };
};
