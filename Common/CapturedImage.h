#pragma once

#include <cstdint>

namespace OpenALRF
{
   struct CapturedImage
   {
      unsigned char *Buffer;
      unsigned long BufferLength;
      unsigned int Width;
      unsigned int Height;
      unsigned int Channels;
      int64_t Sum;
   };
};
