#pragma once

#include <string>
#include "../Common/Types.h"
#include "../System/Module.h"

namespace OpenALRF
{
   struct Sensor1DData
   {
      timestamp_t Timestamp;
      double Data;
   };

   class ISensor1D : public IModule
   {
   protected:
      std::string Identifier;
   public:
      ISensor1D(const std::string AIdentifier);

      virtual void PowerOff() = 0;
      virtual void PowerOn() = 0;
      virtual bool IsPowered() = 0;

      virtual Sensor1DData NextValue() = 0;
   };
};
