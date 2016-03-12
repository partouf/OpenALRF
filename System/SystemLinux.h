#pragma once

#include "System.h"

namespace OpenALRF
{
   class SystemLinux : public ISystem
   {
   protected:
      bool RebootTriggered;

      void SystemCmd(std::string ACommand);
   public:
      SystemLinux();

      void RebootNow() override;
      
      void RestartNetworkInterface(const std::string AInterfaceName) override;

      bool ShouldQuit() override;
   };
};