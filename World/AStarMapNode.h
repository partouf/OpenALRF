#pragma once

#include "../AStar/stlastar.h"
#include "MapTypes.h"

namespace OpenALRF
{
   class MapSearchNode
   {
   protected:
      int x;
      int y;
   public:
      MapSearchNode();
      MapSearchNode(int px, int py);

      float GoalDistanceEstimate(const MapSearchNode &nodeGoal) const;
      bool IsGoal(const MapSearchNode &nodeGoal) const;
      bool GetSuccessors(AStarSearch<MapSearchNode> *astarsearch, const MapSearchNode *parent_node) const;
      float GetCost(const MapSearchNode &successor) const;
      bool IsSameState(const MapSearchNode &rhs) const;

      void PrintNodeInfo() const;

      int GetX() const;
      int GetY() const;
   };

   void SetCurrentSearchMap(IMapReader *AMap);
};
