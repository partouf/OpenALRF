#pragma once

#include <stdexcept>

namespace OpenALRF
{
   enum Legenda {
      MapValueFreeToMove = 32,     // ' '
      MapValuePath = 42,           // '*'
      MapValueBadGround = 44,      // ','
      MapValueObstructed = 65,     // 'A'
      MapValueUnknown = 90         // 'Z'
   };

   struct Position {
      double Longitude;
      double Latitude;
      double Direction;
   };

   struct MapPosition {
      int X;
      int Y;
   };

   class EMapCoordsOutOfBounds : public std::runtime_error
   {
   public:
      EMapCoordsOutOfBounds(int X, int Y);
   };

   class IMapReader
   {
   public:
      virtual double GetMapValue(int X, int Y) const = 0;
   };

   class IMapWriter
   {
   public:
      virtual void SetMapValue(int X, int Y, double AValue) = 0;
   };

   class IMapReaderWriter : public IMapReader, public IMapWriter
   {
   public:
      IMapReaderWriter() : IMapReader(), IMapWriter()
      {
      }
   };

   class IMapTransform
   {
   public:
      virtual IMapReaderWriter *Clip8x8(int CenterX, int CenterY) const = 0;
   };
};
