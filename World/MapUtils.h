#pragma once

#include "MapTypes.h"
#include "AStarMapNOde.h"

namespace OpenALRF
{
   class MapUtils
   {
   public:
      static int GetAngleBetweenMapSearchNodes(const OpenALRF::MapSearchNode *ANodeCurrent, const OpenALRF::MapSearchNode *ANodeNext);
      static double GetDistanceBetweenMapSearchNodes(const OpenALRF::MapSearchNode *ANodeCurrent, const OpenALRF::MapSearchNode *ANodeNext);
   };
}
