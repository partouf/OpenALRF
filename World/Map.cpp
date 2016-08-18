#include "Map.h"

#include <iostream>
#include <fstream>
#include <cstring>

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

OpenALRF::Map20x20m::Map20x20m(std::string AFilename) : IMap()
{
   Position00 = { 0, 0, 0 };
   Start = { 0, 0, 0 };

   memset(&MeterMap, 0, 400);

   Filename = AFilename;

   LoadFromFile();
}

float OpenALRF::Map20x20m::GetMapValue(int X, int Y) const
{
   if ((X < 0) || (X > 19) || (Y < 0) || (Y > 19))
   {
      return static_cast<float>(OpenALRF::MapValueUnknown);
   }

   return static_cast<float>(MeterMap[Y][X]);
}

void OpenALRF::Map20x20m::SetMapValue(int X, int Y, unsigned char AValue)
{
   MeterMap[Y][X] = AValue;
}
