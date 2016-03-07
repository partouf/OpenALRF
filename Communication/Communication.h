#pragma once

#include <string>

namespace OpenALRF
{
   class ICommunication
   {
   public:
      virtual void Process() = 0;
   };
};
