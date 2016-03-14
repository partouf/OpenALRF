#pragma once

#include "../System/Module.h"

namespace OpenALRF
{
   class IMainCamera : public IModule
   {
   public:
      virtual void TakePicture() = 0;
   };
};
