#include "MapUtils.h"

int OpenALRF::MapUtils::GetAngleBetweenMapSearchNodes(const OpenALRF::MapSearchNode *ANodeCurrent, const OpenALRF::MapSearchNode *ANodeNext)
{
   int dx = ANodeNext->GetX() - ANodeCurrent->GetX();
   int dy = ANodeNext->GetY() - ANodeCurrent->GetY();

   if ((dy == 0) && (dx < 0))
   {
      return 270;
   }
   else if ((dy == 0) && (dx > 0))
   {
      return 90;
   }
   else if ((dy < 0) && (dx == 0))
   {
      return 0;
   }
   else if ((dy > 0) && (dx == 0))
   {
      return 180;
   }
   else if ((dy != 0) && (dx != 0))
   {
      return static_cast<int>(atan(dy / dx));
   }

   return -1;
}

double OpenALRF::MapUtils::GetDistanceBetweenMapSearchNodes(const OpenALRF::MapSearchNode *ANodeCurrent, const OpenALRF::MapSearchNode *ANodeNext)
{
   double dx = fabs(ANodeCurrent->GetX() - ANodeNext->GetX());
   double dy = fabs(ANodeCurrent->GetY() - ANodeNext->GetY());

   return sqrt(dx*dx + dy*dy);
}
