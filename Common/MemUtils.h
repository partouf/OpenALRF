#pragma once

#include <cstring>

namespace OpenALRF
{
   template <class T>
   inline void NullifyMem(T &p)
   {
      static_assert(std::is_trivial<T>::value, "May not pass a class to NullifyMem");
      memset(&p, 0, sizeof(T));
   }

   template <class T>
   inline void CopyMem(const T *pSource, char *pDest)
   {
      static_assert(std::is_trivial<T>::value, "May not pass a class to CopyMem");
      memcpy(pDest, pSource, sizeof(T));
   }

   template <class T>
   inline void CopyMem(const T *pSource, unsigned char *pDest)
   {
      static_assert(std::is_trivial<T>::value, "May not pass a class to CopyMem");
      memcpy(pDest, pSource, sizeof(T));
   }

   template <class T>
   inline void CopyMem(const char *pSource, T *pDest)
   {
      static_assert(std::is_trivial<T>::value, "May not pass a class to CopyMem");
      memcpy(pDest, pSource, sizeof(T));
   }

   template <class T>
   inline void CopyMem(const unsigned char *pSource, T *pDest)
   {
      static_assert(std::is_trivial<T>::value, "May not pass a class to CopyMem");
      memcpy(pDest, pSource, sizeof(T));
   }
};
