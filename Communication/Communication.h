#pragma once

#include <string>
#include "../System/Module.h"

namespace OpenALRF
{
   class ICommunication : public IModule
   {
   public:
      virtual void Process() = 0;

      virtual void SendToStation(const std::string AMessage) = 0;
   };
};
