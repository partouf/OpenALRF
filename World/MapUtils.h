#pragma once

#include "AStarMapNOde.h"
#include "MapTypes.h"

namespace OpenALRF
{
   class MapUtils
   {
   public:
      static int GetAngleBetweenMapSearchNodes(const OpenALRF::MapSearchNode *ANodeCurrent,
                                               const OpenALRF::MapSearchNode *ANodeNext);
      static double GetDistanceBetweenMapSearchNodes(const OpenALRF::MapSearchNode *ANodeCurrent,
                                                     const OpenALRF::MapSearchNode *ANodeNext);
   };
} // namespace OpenALRF
