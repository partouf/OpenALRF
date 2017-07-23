#pragma once

#include <cstdint>
#include "../World/MapTypes.h"
#include "../System/Module.h"

namespace OpenALRF
{
   class IRemotePilot : public IModule
   {
   public:
      virtual void Forward(distance_t ADistance) = 0;
      virtual void Backward(distance_t ADistance) = 0;
      virtual void Left(degrees_t AAngle) = 0;
      virtual void Right(degrees_t AAngle) = 0;
      virtual void Stop() = 0;
   };
};
