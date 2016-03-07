#pragma once

#include "system.h"

namespace OpenALRF
{
   class SystemLinux : public ISystem
   {
   public:
      SystemLinux();

      void RebootNow();
   };
};