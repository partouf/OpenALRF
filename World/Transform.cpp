#include "Transform.h"
#include "Map.h"
#include "MapTypes.h"

#ifndef min
#define min(X, Y) (((X) < (Y)) ? (X) : (Y))
#endif

#ifndef max
#define max(X, Y) (((X) > (Y)) ? (X) : (Y))
#endif

OpenALRF::IMapReaderWriter * OpenARLF::MapTransform::Clip8x8(int CenterX, int CenterY) const
{
   int TopLeftX = CenterX - 3;
   int TopLeftY = CenterY - 3;

   auto DestMap = new OpenALRF::Map8x8m();

   for (int Y = 0; Y < 8; ++Y)
   {
      for (int X = 0; X < 8; ++X)
      {
         try
         {
            DestMap->SetMapValue(X, Y, SourceMap->GetMapValue(TopLeftX + X, TopLeftY + Y));
         }
         catch (OpenALRF::EMapCoordsOutOfBounds)
         {
            DestMap->SetMapValue(X, Y, OpenALRF::MapValueUnknown);
         }
      }
   }

   return DestMap;
}

uint32_t * OpenARLF::MapTransformUtils::ToRGBAMatrix(const OpenALRF::IMapReader * SourceMap)
{
   auto matrix = new uint32_t[8][8];

   for (int Y = 0; Y < 8; ++Y)
   {
      for (int X = 0; X < 8; ++X)
      {
         double loc = SourceMap->GetMapValue(X, Y);
         uint32_t rgba = 0xDEB88700;

         if (loc == OpenALRF::Legenda::MapValueBadGround)
         {
            rgba = 0xff450000;
         }
         else if (loc == OpenALRF::Legenda::MapValueFreeToMove)
         {
            rgba = 0x00000000;
         }
         else if (loc == OpenALRF::Legenda::MapValueObstructed)
         {
            rgba = 0xff000000;
         }
         else if (loc == OpenALRF::Legenda::MapValuePath)
         {
            rgba = 0x00ff0000;
         }
         else if (loc == OpenALRF::Legenda::MapValueUnknown)
         {
            rgba = 0xDEB88700;
         }

         matrix[Y][X] = rgba;
      }
   }

   return reinterpret_cast<uint32_t *>(matrix);
}

OpenARLF::MapTransform::MapTransform(const OpenALRF::IMapReader * SourceMap) : IMapTransform()
{
   this->SourceMap = SourceMap;
}
