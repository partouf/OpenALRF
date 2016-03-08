#pragma once

#include "System.h"

namespace OpenALRF
{
   class SystemLinux : public ISystem
   {
   public:
      SystemLinux();

      void RebootNow();
   };
};