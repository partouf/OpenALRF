#pragma once

#include <string>
#include "Module.h"
#include "../Common/Types.h"

namespace OpenALRF
{
   class ISystem : public IModule
   {
   protected:
      OpenALRF::status_t SuggestedStatus;
   public:
      virtual OpenALRF::status_t CurrentStatus();
      virtual void ChangeStatus(OpenALRF::status_t ANewStatus);

      virtual void RebootNow() = 0;

      virtual bool HasValidActiveNetwork() = 0;

      virtual void RestartNetworkInterface(const std::string AInterfaceName) = 0;

      virtual bool ShouldQuit() = 0;
   };
};
