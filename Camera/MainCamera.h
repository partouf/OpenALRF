#pragma once

#include "../System/Module.h"
#include "../Common/CapturedImage.h"

namespace OpenALRF
{
   class IMainCamera : public IModule
   {
   public:
      virtual void TakePicture() = 0;
      virtual CapturedImage GetLatestImage() = 0;
   };
};
