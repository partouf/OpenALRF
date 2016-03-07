#pragma once

#include <cstdint>

namespace OpenALRF
{
   typedef int32_t distance_t;
   typedef int8_t degrees_t;

   class IRemotePilot
   {
   public:
      virtual void Forward(distance_t ADistance) = 0;
      virtual void Backward(distance_t ADistance) = 0;
      virtual void Left(degrees_t AAngle) = 0;
      virtual void Right(degrees_t AAngle) = 0;
      virtual void Stop() = 0;
   };
};
