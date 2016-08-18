#pragma once

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

   class IMap
   {
   public:
      virtual float GetMapValue(int X, int Y) const = 0;
   };
};
