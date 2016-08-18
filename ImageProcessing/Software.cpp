#include "Software.h"

#include <iostream>
#include <fstream>
#include <algorithm>

#ifndef min
#define min(X, Y) (((X) < (Y)) ? (X) : (Y))
#endif

#ifndef max
#define max(X, Y) (((X) > (Y)) ? (X) : (Y))
#endif

OpenALRF::ImageProcessingSoftware::ImageProcessingSoftware()
{
   Original.Buffer = nullptr;
   Original.BufferLength = 0;
   Grayscale.Buffer = nullptr;
   Grayscale.BufferLength = 0;
   ObjectMask.Buffer = nullptr;
   ObjectMask.BufferLength = 0;
}

OpenALRF::ImageProcessingSoftware::~ImageProcessingSoftware()
{
}

void OpenALRF::ImageProcessingSoftware::Initialize(const CapturedImage AImage)
{
   Original = AImage;

   WriteToBMP("original.bmp", AImage);
}

bool OpenALRF::ImageProcessingSoftware::AllocateBuffer(CapturedImage * AImage)
{
   AImage->BufferLength = AImage->Width * AImage->Height * AImage->Channels;
   AImage->Buffer = new unsigned char[AImage->BufferLength];
   if (AImage->Buffer == nullptr)
   {
      AImage->BufferLength = 0;
      std::cerr << "Couldn't allocate buffer for image" << std::endl;
      return false;
   }
   else
   {
      memset(AImage->Buffer, 0, AImage->BufferLength);
   }

   return true;
}

void OpenALRF::ImageProcessingSoftware::WriteToBMP(std::string AFilename, const OpenALRF::CapturedImage AImage)
{
   // mimeType = "image/bmp";

   unsigned char file[14] = {
      'B','M', // magic
      0,0,0,0, // size in bytes
      0,0, // app data
      0,0, // app data
      40 + 14,0,0,0 // start of data offset
   };


   unsigned char info[40] = {
      40,0,0,0, // info hd size
      0,0,0,0, // width
      0,0,0,0, // heigth
      1,0, // number color planes
      24,0, // bits per pixel
      0,0,0,0, // compression is none
      0,0,0,0, // image bits size
      0x13,0x0B,0,0, // horz resoluition in pixel / m
      0x13,0x0B,0,0, // vert resolutions (0x03C3 = 96 dpi, 0x0B13 = 72 dpi)
      0,0,0,0, // #colors in pallete
      0,0,0,0, // #important colors
   };

   int w = AImage.Width;
   int h = AImage.Height;

   int padSize = ((4 - AImage.Channels) * w % 4) % 4;
   int sizeData = w*h * AImage.Channels + h*padSize;
   int sizeAll = sizeData + sizeof(file) + sizeof(info);

   file[2] = (unsigned char)(sizeAll);
   file[3] = (unsigned char)(sizeAll >> 8);
   file[4] = (unsigned char)(sizeAll >> 16);
   file[5] = (unsigned char)(sizeAll >> 24);

   info[4] = (unsigned char)(w);
   info[5] = (unsigned char)(w >> 8);
   info[6] = (unsigned char)(w >> 16);
   info[7] = (unsigned char)(w >> 24);

   info[8] = (unsigned char)(h);
   info[9] = (unsigned char)(h >> 8);
   info[10] = (unsigned char)(h >> 16);
   info[11] = (unsigned char)(h >> 24);

   info[20] = (unsigned char)(sizeData);
   info[21] = (unsigned char)(sizeData >> 8);
   info[22] = (unsigned char)(sizeData >> 16);
   info[23] = (unsigned char)(sizeData >> 24);

   std::ofstream stream;
   stream.open(AFilename, std::ios_base::out | std::ios_base::binary);

   stream.write((char*)file, sizeof(file));
   stream.write((char*)info, sizeof(info));

   unsigned char pad[3] = { 0,0,0 };

   for (int y = 0; y<h; y++)
   {
      for (int x = 0; x<w; x++)
      {
         unsigned char pixel[3];
         if (AImage.Channels == 3)
         {
            pixel[0] = AImage.Buffer[y * AImage.Width * AImage.Channels + x * AImage.Channels + 0];
            pixel[1] = AImage.Buffer[y * AImage.Width * AImage.Channels + x * AImage.Channels + 1];
            pixel[2] = AImage.Buffer[y * AImage.Width * AImage.Channels + x * AImage.Channels + 2];
         }
         else if (AImage.Channels == 1)
         {
            pixel[0] = AImage.Buffer[y * AImage.Width * AImage.Channels + x * AImage.Channels + 0];
            pixel[1] = AImage.Buffer[y * AImage.Width * AImage.Channels + x * AImage.Channels + 0];
            pixel[2] = AImage.Buffer[y * AImage.Width * AImage.Channels + x * AImage.Channels + 0];
         }

         stream.write((char*)pixel, 3);
      }
      stream.write((char*)pad, padSize);
   }
}

OpenALRF::CapturedImage OpenALRF::ImageProcessingSoftware::NewImageFromTemplate(const CapturedImage ATemplateImage)
{
   OpenALRF::CapturedImage NewImage;
   NewImage.Width = ATemplateImage.Width;
   NewImage.Height = ATemplateImage.Height;
   NewImage.Channels = ATemplateImage.Channels;
   NewImage.Sum = 0;
   AllocateBuffer(&NewImage);

   return NewImage;
}

bool OpenALRF::ImageProcessingSoftware::MakeGrayscaleImage()
{
   Grayscale.Width = Original.Width;
   Grayscale.Height = Original.Height;
   Grayscale.Channels = 1;
   Grayscale.Buffer = nullptr;
   Grayscale.BufferLength = 0;

   unsigned long InPtr = 0;
   unsigned long OutPtr = 0;

   if (Original.Channels == 3)
   {
      AllocateBuffer(&Grayscale);

      while (InPtr < Original.BufferLength)
      {
         double gray = Original.Buffer[InPtr + 0] * 0.2126 + Original.Buffer[InPtr + 1] * 0.7152 + Original.Buffer[InPtr + 2] * 0.0722;
         Grayscale.Buffer[OutPtr] = (unsigned char)gray;

         InPtr += 3;
         OutPtr++;
      }

      return true;
   }
   else
   {
      std::cerr << "Image format not supported" << std::endl;
      return false;
   }
}

bool SimularityCheckAndFill(const OpenALRF::CapturedImage AInputImage, OpenALRF::CapturedImage AOutputImage, unsigned long ACurrentPos, unsigned long ACheckPos, bool ACompareV)
{
   unsigned char CurrentColor = AInputImage.Buffer[ACurrentPos];
   unsigned char CheckColor = AInputImage.Buffer[ACheckPos];

   if (ACompareV)
   {
      CurrentColor /= 2.55;
      CheckColor /= 2.55;
   }

   if (abs(CurrentColor - CheckColor) <= 1)
   {
      unsigned char FillColor = AOutputImage.Buffer[ACheckPos];
      if (FillColor == 0)
      {
         if (CheckColor == 0)
         {
            FillColor = 1;
         }
         else
         {
            FillColor = CheckColor;
         }

         AOutputImage.Buffer[ACheckPos] = FillColor;
      }

      AOutputImage.Buffer[ACurrentPos] = FillColor;

      return true;
   }

   return false;
}

OpenALRF::CapturedImage OpenALRF::ImageProcessingSoftware::SimularityFill(const OpenALRF::CapturedImage AInputImage)
{
   OpenALRF::CapturedImage OutputImage = NewImageFromTemplate(AInputImage);

   unsigned long Ptr = 0;
   for (unsigned long y = 1; y < AInputImage.Height - 1; ++y)
   {
      unsigned long CurrentLine = y * AInputImage.Width;

      for (unsigned long x = 1; x < AInputImage.Width - 1; ++x)
      {
         Ptr = CurrentLine + x;
         unsigned long yminus1 = (y - 1) * AInputImage.Width + x;

         if (SimularityCheckAndFill(AInputImage, OutputImage, Ptr, Ptr - 1, true))
         {
            SimularityCheckAndFill(OutputImage, OutputImage, Ptr, yminus1, false);
         }
         else if (SimularityCheckAndFill(AInputImage, OutputImage, Ptr, yminus1, true))
         {
            SimularityCheckAndFill(OutputImage, OutputImage, Ptr, Ptr - 1, false);
         }
      }
   }

   return OutputImage;
}

OpenALRF::CapturedImage OpenALRF::ImageProcessingSoftware::ApplyMask3x3(double mask[3][3], const OpenALRF::CapturedImage AInputImage)
{
   OpenALRF::CapturedImage OutputImage = NewImageFromTemplate(AInputImage);

   unsigned long Ptr = 0;
   for (unsigned long y = 1; y < AInputImage.Height - 1; ++y)
   {
      for (unsigned long x = 1; x < AInputImage.Width - 1; ++x)
      {
         double sum = 0;
         unsigned long yminus1 = (y - 1) * AInputImage.Width;
         sum +=
            mask[0][0] * AInputImage.Buffer[yminus1 + x - 1] +
            mask[0][1] * AInputImage.Buffer[yminus1 + x] +
            mask[0][2] * AInputImage.Buffer[yminus1 + x + 1];

         Ptr = y * AInputImage.Width + x;
         sum +=
            mask[1][0] * AInputImage.Buffer[Ptr - 1] +
            mask[1][1] * AInputImage.Buffer[Ptr] +
            mask[1][2] * AInputImage.Buffer[Ptr + 1];

         unsigned long yplus1 = (y + 1) * AInputImage.Width;
         sum +=
            mask[2][0] * AInputImage.Buffer[yplus1 + x - 1] +
            mask[2][1] * AInputImage.Buffer[yplus1 + x] +
            mask[2][2] * AInputImage.Buffer[yplus1 + x + 1];

         OutputImage.Buffer[Ptr] = static_cast<unsigned char>(sum / 25.0);
         OutputImage.Sum += OutputImage.Buffer[Ptr];
      }
   }

   return OutputImage;
}

OpenALRF::CapturedImage OpenALRF::ImageProcessingSoftware::DenoiseAndConnect(const OpenALRF::CapturedImage AInputImage)
{
   OpenALRF::CapturedImage OutputImage = NewImageFromTemplate(AInputImage);

   for (unsigned long y = 1; y < AInputImage.Height - 1; ++y)
   {
      for (unsigned long x = 1; x < AInputImage.Width - 1; ++x)
      {
         double sum = 0;
         unsigned long yminus1 = (y - 1) * AInputImage.Width + x;
         unsigned long Ptr = y * AInputImage.Width + x;
         unsigned long yplus1 = (y + 1) * AInputImage.Width + x;

         std::vector<unsigned char> Light;
         Light.reserve(9);
         std::vector<unsigned char> Dark;
         Dark.reserve(9);

         unsigned long Pos;
         
         Pos = yminus1 - 1;
         if (AInputImage.Buffer[Pos] < 127) Dark.push_back(AInputImage.Buffer[Pos]);
         else Light.push_back(AInputImage.Buffer[Pos]);

         Pos = yminus1;
         if (AInputImage.Buffer[Pos] < 127) Dark.push_back(AInputImage.Buffer[Pos]);
         else Light.push_back(AInputImage.Buffer[Pos]);

         Pos = yminus1 + 1;
         if (AInputImage.Buffer[Pos] < 127) Dark.push_back(AInputImage.Buffer[Pos]);
         else Light.push_back(AInputImage.Buffer[Pos]);

         Pos = Ptr - 1;
         if (AInputImage.Buffer[Pos] < 127) Dark.push_back(AInputImage.Buffer[Pos]);
         else Light.push_back(AInputImage.Buffer[Pos]);

         Pos = Ptr;
         if (AInputImage.Buffer[Pos] < 127) Dark.push_back(AInputImage.Buffer[Pos]);
         else Light.push_back(AInputImage.Buffer[Pos]);

         Pos = Ptr + 1;
         if (AInputImage.Buffer[Pos] < 127) Dark.push_back(AInputImage.Buffer[Pos]);
         else Light.push_back(AInputImage.Buffer[Pos]);

         Pos = yplus1 - 1;
         if (AInputImage.Buffer[Pos] < 127) Dark.push_back(AInputImage.Buffer[Pos]);
         else Light.push_back(AInputImage.Buffer[Pos]);

         Pos = yplus1;
         if (AInputImage.Buffer[Pos] < 127) Dark.push_back(AInputImage.Buffer[Pos]);
         else Light.push_back(AInputImage.Buffer[Pos]);

         Pos = yplus1 + 1;
         if (AInputImage.Buffer[Pos] < 127) Dark.push_back(AInputImage.Buffer[Pos]);
         else Light.push_back(AInputImage.Buffer[Pos]);

         std::sort(Light.begin(), Light.end());
         std::sort(Dark.begin(), Dark.end());

         if (Dark.size() > Light.size())
         {
            OutputImage.Buffer[Ptr] = Dark.at(Dark.size() / 2);
         }
         else
         {
            OutputImage.Buffer[Ptr] = Light.at(Light.size() / 2);
         }
      }
   }

   return OutputImage;
}

OpenALRF::CapturedImage OpenALRF::ImageProcessingSoftware::ApplyMask3x3Median(double mask[3][3], const OpenALRF::CapturedImage AInputImage)
{
   OpenALRF::CapturedImage OutputImage = NewImageFromTemplate(AInputImage);

   std::vector<unsigned char> numbers;
   numbers.reserve(9);
      
   unsigned long Ptr = 0;
   for (unsigned long y = 1; y < AInputImage.Height - 1; ++y)
   {
      for (unsigned long x = 1; x < AInputImage.Width - 1; ++x)
      {
         numbers.clear();

         unsigned long yminus1 = (y - 1) * AInputImage.Width;
         numbers.push_back(mask[0][0] * AInputImage.Buffer[yminus1 + x - 1]);
         numbers.push_back(mask[0][1] * AInputImage.Buffer[yminus1 + x]);
         numbers.push_back(mask[0][2] * AInputImage.Buffer[yminus1 + x + 1]);

         Ptr = y * AInputImage.Width + x;
         numbers.push_back(mask[1][0] * AInputImage.Buffer[Ptr - 1]);
         numbers.push_back(mask[1][1] * AInputImage.Buffer[Ptr]);
         numbers.push_back(mask[1][2] * AInputImage.Buffer[Ptr + 1]);

         unsigned long yplus1 = (y + 1) * AInputImage.Width;
         numbers.push_back(mask[2][0] * AInputImage.Buffer[yplus1 + x - 1]);
         numbers.push_back(mask[2][1] * AInputImage.Buffer[yplus1 + x]);
         numbers.push_back(mask[2][2] * AInputImage.Buffer[yplus1 + x + 1]);

         OutputImage.Buffer[Ptr] = GetMedianForValue(numbers);
         OutputImage.Sum += OutputImage.Buffer[Ptr];
      }
   }

   return OutputImage;
}

OpenALRF::CapturedImage OpenALRF::ImageProcessingSoftware::ApplyMask5x5(double mask[5][5], const OpenALRF::CapturedImage AInputImage)
{
   OpenALRF::CapturedImage OutputImage = NewImageFromTemplate(AInputImage);

   // todo: find optimized way to do the edges, but for now skip them

   unsigned long Ptr = 0;
   for (unsigned long y = 2; y < AInputImage.Height - 2; ++y)
   {
      for (unsigned long x = 2; x < AInputImage.Width - 2; ++x)
      {
         double sum = 0;
         unsigned long yminus2 = (y - 2) * AInputImage.Width;
         sum +=
            mask[0][0] * AInputImage.Buffer[yminus2 + x - 2] +
            mask[0][1] * AInputImage.Buffer[yminus2 + x - 1] +
            mask[0][2] * AInputImage.Buffer[yminus2 + x] +
            mask[0][3] * AInputImage.Buffer[yminus2 + x + 1] +
            mask[0][4] * AInputImage.Buffer[yminus2 + x + 2];

         unsigned long yminus1 = (y - 1) * AInputImage.Width;
         sum +=
            mask[1][0] * AInputImage.Buffer[yminus1 + x - 2] +
            mask[1][1] * AInputImage.Buffer[yminus1 + x - 1] +
            mask[1][2] * AInputImage.Buffer[yminus1 + x] +
            mask[1][3] * AInputImage.Buffer[yminus1 + x + 1] +
            mask[1][4] * AInputImage.Buffer[yminus1 + x + 2];

         Ptr = y * AInputImage.Width + x;
         sum +=
            mask[2][0] * AInputImage.Buffer[Ptr - 2] +
            mask[2][1] * AInputImage.Buffer[Ptr - 1] +
            mask[2][2] * AInputImage.Buffer[Ptr] +
            mask[2][3] * AInputImage.Buffer[Ptr + 1] +
            mask[2][4] * AInputImage.Buffer[Ptr + 2];

         unsigned long yplus1 = (y + 1) * AInputImage.Width;
         sum +=
            mask[3][0] * AInputImage.Buffer[yplus1 + x - 2] +
            mask[3][1] * AInputImage.Buffer[yplus1 + x - 1] +
            mask[3][2] * AInputImage.Buffer[yplus1 + x] +
            mask[3][3] * AInputImage.Buffer[yplus1 + x + 1] +
            mask[3][4] * AInputImage.Buffer[yplus1 + x + 2];

         unsigned long yplus2 = (y + 2) * AInputImage.Width;
         sum +=
            mask[4][0] * AInputImage.Buffer[yplus2 + x - 2] +
            mask[4][1] * AInputImage.Buffer[yplus2 + x - 1] +
            mask[4][2] * AInputImage.Buffer[yplus2 + x] +
            mask[4][3] * AInputImage.Buffer[yplus2 + x + 1] +
            mask[4][4] * AInputImage.Buffer[yplus2 + x + 2];

         OutputImage.Buffer[Ptr] = static_cast<unsigned char>(abs(sum) / 25.0);
         OutputImage.Sum += OutputImage.Buffer[Ptr];
      }
   }

   return OutputImage;
}

template< typename T >
typename std::vector<T>::iterator
insert_sorted(std::vector<T> & vec, T const& item)
{
   return vec.insert
      (
         std::upper_bound(vec.begin(), vec.end(), item),
         item
         );
}

OpenALRF::CapturedImage OpenALRF::ImageProcessingSoftware::ApplyMask5x5Median(double mask[5][5], const OpenALRF::CapturedImage AInputImage)
{
   OpenALRF::CapturedImage OutputImage = NewImageFromTemplate(AInputImage);

   std::vector<unsigned char> numbers;

   unsigned long Ptr = 0;
   for (unsigned long y = 2; y < AInputImage.Height - 2; ++y)
   {
      for (unsigned long x = 2; x < AInputImage.Width - 2; ++x)
      {
         double sum = 0;
         unsigned long yminus2 = (y - 2) * AInputImage.Width + x;

         numbers.clear();
         numbers.reserve(25);
         insert_sorted<unsigned char>(numbers, mask[0][0] * AInputImage.Buffer[yminus2 - 2]);
         insert_sorted<unsigned char>(numbers, mask[0][1] * AInputImage.Buffer[yminus2 - 1]);
         insert_sorted<unsigned char>(numbers, mask[0][2] * AInputImage.Buffer[yminus2]);
         insert_sorted<unsigned char>(numbers, mask[0][3] * AInputImage.Buffer[yminus2 + 1]);
         insert_sorted<unsigned char>(numbers, mask[0][4] * AInputImage.Buffer[yminus2 + 2]);

         unsigned long yminus1 = (y - 1) * AInputImage.Width + x;
         insert_sorted<unsigned char>(numbers, mask[1][0] * AInputImage.Buffer[yminus1 - 2]);
         insert_sorted<unsigned char>(numbers, mask[1][1] * AInputImage.Buffer[yminus1 - 1]);
         insert_sorted<unsigned char>(numbers, mask[1][2] * AInputImage.Buffer[yminus1]);
         insert_sorted<unsigned char>(numbers, mask[1][3] * AInputImage.Buffer[yminus1 + 1]);
         insert_sorted<unsigned char>(numbers, mask[1][4] * AInputImage.Buffer[yminus1 + 2]);

         Ptr = y * AInputImage.Width + x;
         insert_sorted<unsigned char>(numbers, mask[2][0] * AInputImage.Buffer[Ptr - 2]);
         insert_sorted<unsigned char>(numbers, mask[2][1] * AInputImage.Buffer[Ptr - 1]);
         insert_sorted<unsigned char>(numbers, mask[2][2] * AInputImage.Buffer[Ptr]);
         insert_sorted<unsigned char>(numbers, mask[2][3] * AInputImage.Buffer[Ptr + 1]);
         insert_sorted<unsigned char>(numbers, mask[2][4] * AInputImage.Buffer[Ptr + 2]);

         unsigned long yplus1 = (y + 1) * AInputImage.Width + x;
         insert_sorted<unsigned char>(numbers, mask[3][0] * AInputImage.Buffer[yplus1 - 2]);
         insert_sorted<unsigned char>(numbers, mask[3][1] * AInputImage.Buffer[yplus1 - 1]);
         insert_sorted<unsigned char>(numbers, mask[3][2] * AInputImage.Buffer[yplus1]);
         insert_sorted<unsigned char>(numbers, mask[3][3] * AInputImage.Buffer[yplus1 + 1]);
         insert_sorted<unsigned char>(numbers, mask[3][4] * AInputImage.Buffer[yplus1 + 2]);

         unsigned long yplus2 = (y + 2) * AInputImage.Width + x;
         insert_sorted<unsigned char>(numbers, mask[4][0] * AInputImage.Buffer[yplus2 - 2]);
         insert_sorted<unsigned char>(numbers, mask[4][1] * AInputImage.Buffer[yplus2 - 1]);
         insert_sorted<unsigned char>(numbers, mask[4][2] * AInputImage.Buffer[yplus2]);
         insert_sorted<unsigned char>(numbers, mask[4][3] * AInputImage.Buffer[yplus2 + 1]);
         insert_sorted<unsigned char>(numbers, mask[4][4] * AInputImage.Buffer[yplus2 + 2]);

         OutputImage.Buffer[Ptr] = numbers.at(12);
         OutputImage.Sum += OutputImage.Buffer[Ptr];
      }
   }

   return OutputImage;
}

OpenALRF::CapturedImage OpenALRF::ImageProcessingSoftware::ApplyMask5x5SkipColor(double mask[5][5], const OpenALRF::CapturedImage AInputImage, unsigned char ASkipColor)
{
   OpenALRF::CapturedImage OutputImage = NewImageFromTemplate(AInputImage);

   for (unsigned long y = 2; y < AInputImage.Height - 2; ++y)
   {
      for (unsigned long x = 2; x < AInputImage.Width - 2; ++x)
      {
         int skipcount = 0;
         double sum = 0;
         unsigned long yminus2 = (y - 2) * AInputImage.Width + x;
         sum +=
            mask[0][0] * AInputImage.Buffer[yminus2 - 2] +
            mask[0][1] * AInputImage.Buffer[yminus2 - 1] +
            mask[0][2] * AInputImage.Buffer[yminus2] +
            mask[0][3] * AInputImage.Buffer[yminus2 + 1] +
            mask[0][4] * AInputImage.Buffer[yminus2 + 2];

         if (AInputImage.Buffer[yminus2 - 2] <= ASkipColor) skipcount++;
         if (AInputImage.Buffer[yminus2 - 1] <= ASkipColor) skipcount++;
         if (AInputImage.Buffer[yminus2] <= ASkipColor) skipcount++;
         if (AInputImage.Buffer[yminus2 + 1] <= ASkipColor) skipcount++;
         if (AInputImage.Buffer[yminus2 + 2] <= ASkipColor) skipcount++;

         unsigned long yminus1 = (y - 1) * AInputImage.Width + x;
         sum +=
            mask[1][0] * AInputImage.Buffer[yminus1 - 2] +
            mask[1][1] * AInputImage.Buffer[yminus1 - 1] +
            mask[1][2] * AInputImage.Buffer[yminus1] +
            mask[1][3] * AInputImage.Buffer[yminus1 + 1] +
            mask[1][4] * AInputImage.Buffer[yminus1 + 2];

         if (AInputImage.Buffer[yminus1 - 2] <= ASkipColor) skipcount++;
         if (AInputImage.Buffer[yminus1 - 1] <= ASkipColor) skipcount++;
         if (AInputImage.Buffer[yminus1] <= ASkipColor) skipcount++;
         if (AInputImage.Buffer[yminus1 + 1] <= ASkipColor) skipcount++;
         if (AInputImage.Buffer[yminus1 + 2] <= ASkipColor) skipcount++;

         unsigned long Ptr = y * AInputImage.Width + x;
         sum +=
            mask[2][0] * AInputImage.Buffer[Ptr - 2] +
            mask[2][1] * AInputImage.Buffer[Ptr - 1] +
            mask[2][2] * AInputImage.Buffer[Ptr] +
            mask[2][3] * AInputImage.Buffer[Ptr + 1] +
            mask[2][4] * AInputImage.Buffer[Ptr + 2];

         if (AInputImage.Buffer[Ptr - 2] <= ASkipColor) skipcount++;
         if (AInputImage.Buffer[Ptr - 1] <= ASkipColor) skipcount++;
         if (AInputImage.Buffer[Ptr] <= ASkipColor) skipcount++;
         if (AInputImage.Buffer[Ptr + 1] <= ASkipColor) skipcount++;
         if (AInputImage.Buffer[Ptr + 2] <= ASkipColor) skipcount++;

         unsigned long yplus1 = (y + 1) * AInputImage.Width + x;
         sum +=
            mask[3][0] * AInputImage.Buffer[yplus1 - 2] +
            mask[3][1] * AInputImage.Buffer[yplus1 - 1] +
            mask[3][2] * AInputImage.Buffer[yplus1] +
            mask[3][3] * AInputImage.Buffer[yplus1 + 1] +
            mask[3][4] * AInputImage.Buffer[yplus1 + 2];

         if (AInputImage.Buffer[yplus1 - 2] <= ASkipColor) skipcount++;
         if (AInputImage.Buffer[yplus1 - 1] <= ASkipColor) skipcount++;
         if (AInputImage.Buffer[yplus1] <= ASkipColor) skipcount++;
         if (AInputImage.Buffer[yplus1 + 1] <= ASkipColor) skipcount++;
         if (AInputImage.Buffer[yplus1 + 2] <= ASkipColor) skipcount++;

         unsigned long yplus2 = (y + 2) * AInputImage.Width + x;
         sum +=
            mask[4][0] * AInputImage.Buffer[yplus2 - 2] +
            mask[4][1] * AInputImage.Buffer[yplus2 - 1] +
            mask[4][2] * AInputImage.Buffer[yplus2] +
            mask[4][3] * AInputImage.Buffer[yplus2 + 1] +
            mask[4][4] * AInputImage.Buffer[yplus2 + 2];

         if (AInputImage.Buffer[yplus2 - 2] <= ASkipColor) skipcount++;
         if (AInputImage.Buffer[yplus2 - 1] <= ASkipColor) skipcount++;
         if (AInputImage.Buffer[yplus2] <= ASkipColor) skipcount++;
         if (AInputImage.Buffer[yplus2 + 1] <= ASkipColor) skipcount++;
         if (AInputImage.Buffer[yplus2 + 2] <= ASkipColor) skipcount++;

         OutputImage.Buffer[Ptr] = static_cast<unsigned char>(sum / (1.0 * (25 - skipcount)));
         OutputImage.Sum += OutputImage.Buffer[Ptr];
      }
   }

   return OutputImage;
}

std::vector<unsigned char> OpenALRF::ImageProcessingSoftware::GetDiffs(std::vector<unsigned char> ANumbers)
{
   std::vector<unsigned char> diffs;
   diffs.reserve(ANumbers.size() / 2 + 1);

   for (unsigned int i = 1; i < ANumbers.size(); ++i)
   {
      diffs.push_back(ANumbers[i] - ANumbers[i - 1]);
   }

   return diffs;
}

std::vector<unsigned char> OpenALRF::ImageProcessingSoftware::BlowUpVectorContrast(std::vector<unsigned char> ANumbers)
{
   std::sort(ANumbers.begin(), ANumbers.end());

   std::vector<unsigned char> Scaled;
   Scaled.reserve(ANumbers.size());

   unsigned char LowValue = ANumbers.front();
   unsigned char HighValue = ANumbers.back();

   double multiplier = 255.0 / (HighValue-LowValue);

   for (auto Value : ANumbers)
   {
      Scaled.push_back(static_cast<unsigned char>((Value - LowValue) * multiplier));
   }
   
   return Scaled;
}

unsigned char OpenALRF::ImageProcessingSoftware::GetMedianForValue(std::vector<unsigned char> ANumbers)
{
   std::sort(ANumbers.begin(), ANumbers.end());

   return ANumbers[static_cast<size_t>(ANumbers.size() / 2)];
}

OpenALRF::CapturedImage OpenALRF::ImageProcessingSoftware::PlaneDetection(const OpenALRF::CapturedImage AInputImage)
{
   OpenALRF::CapturedImage OutputImage = NewImageFromTemplate(AInputImage);
   std::vector<unsigned char> numbers;
   numbers.reserve(25);
   
   for (unsigned long y = 2; y < AInputImage.Height - 2; ++y)
   {
      for (unsigned long x = 2; x < AInputImage.Width - 2; ++x)
      {
         unsigned long yminus1 = (y - 1) * AInputImage.Width;
         unsigned long yminus2 = (y - 2) * AInputImage.Width;
         unsigned long yzero = y * AInputImage.Width;
         unsigned long yplus1 = (y + 1) * AInputImage.Width;
         unsigned long yplus2 = (y + 2) * AInputImage.Width;

         numbers.clear();

         numbers.push_back(AInputImage.Buffer[yminus2 + x - 2]);
         numbers.push_back(AInputImage.Buffer[yminus2 + x - 1]);
         numbers.push_back(AInputImage.Buffer[yminus2 + x]);
         numbers.push_back(AInputImage.Buffer[yminus2 + x + 1]);
         numbers.push_back(AInputImage.Buffer[yminus2 + x + 2]);

         numbers.push_back(AInputImage.Buffer[yminus1 + x - 2]);
         numbers.push_back(AInputImage.Buffer[yminus1 + x - 1]);
         numbers.push_back(AInputImage.Buffer[yminus1 + x]);
         numbers.push_back(AInputImage.Buffer[yminus1 + x + 1]);
         numbers.push_back(AInputImage.Buffer[yminus1 + x + 2]);

         numbers.push_back(AInputImage.Buffer[yzero + x - 2]);
         numbers.push_back(AInputImage.Buffer[yzero + x - 1]);
         numbers.push_back(AInputImage.Buffer[yzero + x]);
         numbers.push_back(AInputImage.Buffer[yzero + x + 1]);
         numbers.push_back(AInputImage.Buffer[yzero + x + 2]);

         numbers.push_back(AInputImage.Buffer[yplus1 + x - 2]);
         numbers.push_back(AInputImage.Buffer[yplus1 + x - 1]);
         numbers.push_back(AInputImage.Buffer[yplus1 + x]);
         numbers.push_back(AInputImage.Buffer[yplus1 + x + 1]);
         numbers.push_back(AInputImage.Buffer[yplus1 + x + 2]);

         numbers.push_back(AInputImage.Buffer[yplus2 + x - 2]);
         numbers.push_back(AInputImage.Buffer[yplus2 + x - 1]);
         numbers.push_back(AInputImage.Buffer[yplus2 + x]);
         numbers.push_back(AInputImage.Buffer[yplus2 + x + 1]);
         numbers.push_back(AInputImage.Buffer[yplus2 + x + 2]);

         OutputImage.Buffer[yzero + x] = GetMedianForValue(numbers);
         OutputImage.Sum += OutputImage.Buffer[yzero + x];
      }
   }

   return OutputImage;
}

OpenALRF::CapturedImage OpenALRF::ImageProcessingSoftware::MakeMonoImage(const OpenALRF::CapturedImage AInputImage, unsigned char ACutoffPoint)
{
   OpenALRF::CapturedImage OutputImage = NewImageFromTemplate(AInputImage);

   for (unsigned long Ptr = 0; Ptr < AInputImage.BufferLength; ++Ptr)
   {
      if (AInputImage.Buffer[Ptr] > ACutoffPoint)
      {
         OutputImage.Buffer[Ptr] = 255;
         OutputImage.Sum += OutputImage.Buffer[Ptr];
      }
   }

   return OutputImage;
}

OpenALRF::CapturedImage OpenALRF::ImageProcessingSoftware::FindCutoffMakeMonoImage(const OpenALRF::CapturedImage AInputImage)
{
   unsigned char LowValue = 255;
   unsigned char HighValue = 0;
   for (unsigned long Ptr = 0; Ptr < AInputImage.BufferLength; ++Ptr)
   {
      LowValue = min(AInputImage.Buffer[Ptr], LowValue);
      HighValue = max(AInputImage.Buffer[Ptr], HighValue);
   }

   return MakeMonoImage(AInputImage, (HighValue + LowValue) / 2);
}

OpenALRF::CapturedImage OpenALRF::ImageProcessingSoftware::BlowUpImageContrast(const OpenALRF::CapturedImage AInputImage)
{
   OpenALRF::CapturedImage OutputImage = NewImageFromTemplate(AInputImage);

   unsigned char LowValue = 255;
   unsigned char HighValue = 0;
   for (unsigned long Ptr = 0; Ptr < AInputImage.BufferLength; ++Ptr)
   {
      LowValue = min(AInputImage.Buffer[Ptr], LowValue);
      HighValue = max(AInputImage.Buffer[Ptr], HighValue);
   }

   double multiplier = 255.0 / (HighValue - LowValue);

   for (unsigned long Ptr = 0; Ptr < AInputImage.BufferLength; ++Ptr)
   {
      OutputImage.Buffer[Ptr] = static_cast<unsigned char>((AInputImage.Buffer[Ptr] - LowValue) * multiplier);
      OutputImage.Sum += OutputImage.Buffer[Ptr];
   }

   return OutputImage;
}

bool OpenALRF::ImageProcessingSoftware::MakeObjectMask()
{
   double LoGMask[5][5]
   {
      { 0, 0,-1, 0, 0 },
      { 0,-1,-2,-1, 0 },
      {-1,-2,16,-2,-1 },
      { 0,-1,-2,-1, 0 },
      { 0, 0,-1, 0, 0 }
   };

   double LoGCannyMask[5][5]
   {
      { 2, 4, 5, 4, 2 },
      { 3, 9,12, 9, 4 },
      { 5,12,15,12, 5 },
      { 4, 9,12, 9, 4 },
      { 2, 4, 5, 4, 2 }
   };

   double Blur5Mask[5][5]
   {
      { 1, 1, 1, 1, 1 },
      { 1, 1, 1, 1, 1 },
      { 1, 1, 1, 1, 1 },
      { 1, 1, 1, 1, 1 },
      { 1, 1, 1, 1, 1 }
   };

   double BigNoise[5][5]
   {
      { 1, 1, 1, 1, 1 },
      { 1, 1, 0, 1, 1 },
      { 1, 0, 0, 0, 1 },
      { 1, 1, 0, 1, 1 },
      { 1, 1, 1, 1, 1 }
   };

   double Blur3Mask[3][3]
   {
      { 1, 1, 1 },
      { 1, 1, 1 },
      { 1, 1, 1 }
   };

   double SobXMask[3][3]
   {
      {-1, 0, 1 },
      {-2, 0, 2 },
      {-1, 0, 1 }
   };

   double SobYMask[3][3]
   {
      { -1,-2,-1 },
      {  0, 0, 0 },
      {  1, 2, 1 }
   };

   MakeGrayscaleImage();

   if (Grayscale.Buffer != nullptr)
   {
      //WriteToBMP("grayscale.bmp", Grayscale);

      // http://docs.opencv.org/2.4/doc/tutorials/imgproc/imgtrans/canny_detector/canny_detector.html



      CapturedImage Step1 = ApplyMask5x5(LoGCannyMask, Grayscale);
      //WriteToBMP("step1.bmp", Step1);

      CapturedImage Step2a = ApplyMask3x3(SobXMask, Step1);
      //WriteToBMP("step2a.bmp", Step2a);

      CapturedImage Step2b = ApplyMask3x3(SobYMask, Step1);
      //WriteToBMP("step2b.bmp", Step2b);


      double strength = sqrt(pow(Step2a.Sum, 2) + pow(Step2b.Sum, 2));
      double direction = atan(Step2b.Sum / Step2a.Sum);

      // 0, 45, 90 or 135
      direction = round(direction);

      double half = 45 / 2;
      if ((direction > half) || (direction < 45 + half))
      {
         direction = 45;
      }
      else if ((direction > 45 + half) || (direction < 90 + half))
      {
         direction = 90;
      }
      else if ((direction > 90 + half) || (direction < 135 + half))
      {
         direction = 135;
      }
      else
      {
         direction = 0;
      }

      /*
      CapturedImage Denoise = DenoiseAndConnect(MonoLoG);
      WriteToBMP("logdenoise.bmp", Denoise);

      CapturedImage Blowup = BlowUpImageContrast(Denoise);
      WriteToBMP("blowup.bmp", Blowup);

      CapturedImage Filled = SimularityFill(Grayscale);
      WriteToBMP("filled.bmp", Filled);

      CapturedImage BlurredWithSkip = ApplyMask5x5SkipColor(Blur5Mask, Filled, 5);
      WriteToBMP("blurredwithskip.bmp", BlurredWithSkip);

      CapturedImage Filled2 = SimularityFill(BlurredWithSkip);
      WriteToBMP("filled2.bmp", Filled2);

      CapturedImage BlurredWithSkip2 = ApplyMask5x5SkipColor(Blur5Mask, Filled2, 5);
      WriteToBMP("blurredwithskip2.bmp", BlurredWithSkip2);

      CapturedImage Blowup2 = BlowUpImageContrast(BlurredWithSkip2);
      WriteToBMP("blowup2.bmp", Blowup2);

      ObjectMask = PlaneDetection(Blowup2);
      WriteToBMP("planes.bmp", ObjectMask);
      */

      return true;
   }

   return false;
}

unsigned char OpenALRF::ImageProcessingSoftware::GetAverageGrayByte() const
{
   unsigned long valuesum = 0;

   for (unsigned long i = 0; i < Grayscale.BufferLength; ++i)
   {
      valuesum += static_cast<unsigned long>(Grayscale.Buffer[i]);
   }

   return static_cast<unsigned char>(valuesum / Grayscale.BufferLength);
}
