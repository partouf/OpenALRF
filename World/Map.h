#pragma once

#include <string>
#include <vector>

#include "MapTypes.h"

namespace OpenALRF
{
   class Map20x20m: public IMap
   {
   protected:
      std::string Filename;

      Position Position00;
      Position Start;
      unsigned char MeterMap[20][20];

      void LoadFromFile();
      //void Clear();
   public:
      Map20x20m(std::string AFilename);

      virtual float GetMapValue(int X, int Y) const override;

      void SetMapValue(int X, int Y, unsigned char AValue);

      void SaveToFile(const std::string ANewFilename = "");
   };

   class IMapping
   {
   protected:
      //Map20x20m LoadFromFile(Position AMapPosition);
   public:
      //void SetupPerspective(Position APerspective);
   };
};
