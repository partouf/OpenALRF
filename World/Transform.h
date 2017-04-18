#pragma once

#include "MapTypes.h"

namespace OpenARLF
{
   class MapTransform: public OpenALRF::IMapTransform
   {
   protected:
      const OpenALRF::IMapReader *SourceMap;
   public:
      MapTransform(const OpenALRF::IMapReader *SourceMap);

      virtual OpenALRF::IMapReaderWriter * Clip8x8(int CenterX, int CenterY) const override;
   };

   class MapTransformUtils
   {
   public:
      static uint32_t *ToRGBAMatrix(const OpenALRF::IMapReader *SourceMap);
   };
}
