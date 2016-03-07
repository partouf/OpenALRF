#pragma once

#include "Types.h"

namespace OpenALRF
{
   class ICommandQueue
   {
   public:
      virtual void Add(Command ACmd) = 0;
      virtual void Process() = 0;
   };
};
