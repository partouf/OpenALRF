#pragma once

#include "../Common/Types.h"
#include "Module.h"
#include <string>

namespace OpenALRF
{
   class ISystem : public IModule
   {
   protected:
      OpenALRF::Status SuggestedStatus;

   public:
      virtual OpenALRF::Status CurrentStatus() const;
      virtual void ChangeStatus(OpenALRF::Status ANewStatus);

      virtual void RebootNow() = 0;

      virtual bool HasValidActiveNetwork() = 0;

      virtual void RestartNetworkInterface(const std::string AInterfaceName) = 0;

      virtual bool ShouldQuit() = 0;
   };
}; // namespace OpenALRF
