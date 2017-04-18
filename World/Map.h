#pragma once

#include <string>
#include <vector>

#include "MapTypes.h"

namespace OpenALRF
{
   class Map20x20m: public IMapReaderWriter
   {
   protected:
      std::string Filename;

      Position Position00;
      Position Start;
      unsigned char MeterMap[20][20];

      inline bool IsOutOfBounds(int X, int Y) const;

      void LoadFromFile();
      //void Clear();
   public:
      Map20x20m(std::string AFilename);

      void ClearMap();

      virtual double GetMapValue(int X, int Y) const override;

      virtual void SetMapValue(int X, int Y, double AValue) override;

      void SaveToFile(const std::string ANewFilename = "");
   };

   class Map8x8m : public IMapReaderWriter
   {
   protected:
      unsigned char MeterMap[8][8];

      inline bool IsOutOfBounds(int X, int Y) const;
      void ClearMap();
   public:
      Map8x8m();

      virtual double GetMapValue(int X, int Y) const override;

      virtual void SetMapValue(int X, int Y, double AValue) override;
   };
};
