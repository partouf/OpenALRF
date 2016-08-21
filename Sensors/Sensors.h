#pragma once

#include "../System/Module.h"
#include "../Common/Types.h"

using namespace std;

namespace OpenALRF
{
   struct Sensor3DData
   {
      timestamp_t Timestamp;
      double Data1;
      double Data2;
      double Data3;
   };

   class ISensor : public IModule
   {
   protected:
      string Identifier;
   public:
      ISensor(const string AIdentifier);

      virtual string GetIdentifier();

      virtual void PowerOff() = 0;
      virtual void PowerOn() = 0;
      virtual bool IsPowered() = 0;

      virtual Sensor3DData NextValue() = 0;
   };
};
