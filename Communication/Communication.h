#pragma once

#include "../System/Module.h"
#include <string>

namespace OpenALRF
{
   class ICommunication : public IModule
   {
   public:
      virtual void Process() = 0;

      virtual void SendToStation(const std::string AMessage) = 0;
   };
}; // namespace OpenALRF
