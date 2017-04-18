#include "Map.h"

#include <iostream>
#include <fstream>
#include <cstring>

inline bool OpenALRF::Map20x20m::IsOutOfBounds(int X, int Y) const
{
   return (X < 0) || (X > 19) || (Y < 0) || (Y > 19);
}

void OpenALRF::Map20x20m::LoadFromFile()
{
   std::string line;

   std::ifstream fs;
   fs.open(Filename);
   if (fs.is_open())
   {
      int y = 0;
      while (getline(fs, line))
      {
         for (int i = 0; i < 20; i++)
         {
            MeterMap[y][i] = line[i];
         }

         y++;
      }
      fs.close();
   }
}

void OpenALRF::Map20x20m::SaveToFile(const std::string ANewFilename)
{
   std::string line;

   Filename = ANewFilename;

   std::ofstream fs;
   fs.open(Filename);
   if (fs.is_open())
   {
      for (int y = 0; y < 20; ++y)
      {
         fs.write(reinterpret_cast<const char *>(&MeterMap[y]), 20);
         fs << std::endl;
      }

      fs.close();
   }
}

OpenALRF::Map20x20m::Map20x20m(std::string AFilename) : IMapReaderWriter()
{
   Position00 = { 0, 0, 0 };
   Start = { 0, 0, 0 };

   ClearMap();

   Filename = AFilename;

   LoadFromFile();
}

void OpenALRF::Map20x20m::ClearMap()
{
   memset(&MeterMap, 0, 400);
}

double OpenALRF::Map20x20m::GetMapValue(int X, int Y) const
{
   if (IsOutOfBounds(X, Y))
   {
      return static_cast<double>(OpenALRF::MapValueUnknown);
   }

   return static_cast<double>(MeterMap[Y][X]);
}

void OpenALRF::Map20x20m::SetMapValue(int X, int Y, double AValue)
{
   if (IsOutOfBounds(X, Y))
   {
      throw new EMapCoordsOutOfBounds(X, Y);
   }

   MeterMap[Y][X] = static_cast<unsigned char>(AValue);
}

inline bool OpenALRF::Map8x8m::IsOutOfBounds(int X, int Y) const
{
   return (X < 0) || (X > 8) || (Y < 0) || (Y > 8);
}

void OpenALRF::Map8x8m::ClearMap()
{
   memset(&MeterMap, 0, 64);
}

OpenALRF::Map8x8m::Map8x8m(): IMapReaderWriter()
{
   ClearMap();
}

double OpenALRF::Map8x8m::GetMapValue(int X, int Y) const
{
   if (IsOutOfBounds(X, Y))
   {
      throw new EMapCoordsOutOfBounds(X, Y);
   }

   return static_cast<double>(MeterMap[Y][X]);
}

void OpenALRF::Map8x8m::SetMapValue(int X, int Y, double AValue)
{
   if (IsOutOfBounds(X, Y))
   {
      throw new EMapCoordsOutOfBounds(X, Y);
   }

   MeterMap[Y][X] = static_cast<unsigned char>(AValue);
}
