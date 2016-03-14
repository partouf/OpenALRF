#pragma once

#include "Types.h"
#include "../System/Module.h"

namespace OpenALRF
{
   class ICommandQueue : public IModule
   {
   public:
      virtual void Add(Command ACmd) = 0;
      virtual void Process() = 0;
   };
};
