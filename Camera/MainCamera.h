#pragma once

#include "../Common/CapturedImage.h"
#include "../System/Module.h"

namespace OpenALRF
{
   class IMainCamera : public IModule
   {
   public:
      virtual void TakePicture() = 0;
      virtual CapturedImage GetLatestImage() = 0;
   };
}; // namespace OpenALRF
