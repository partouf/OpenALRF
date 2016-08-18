#include "AStarMapNode.h"

OpenALRF::IMap *CurrentSearchMap = nullptr;

OpenALRF::MapSearchNode::MapSearchNode()
{
   x = y = 0;
}

OpenALRF::MapSearchNode::MapSearchNode(int px, int py)
{
   x = px;
   y = py;
}

float OpenALRF::MapSearchNode::GoalDistanceEstimate(const MapSearchNode & nodeGoal) const
{
   return fabsf(x - nodeGoal.x) + fabsf(y - nodeGoal.y);
}

bool OpenALRF::MapSearchNode::IsGoal(const MapSearchNode & nodeGoal) const
{
   return (x == nodeGoal.x) && (y == nodeGoal.y);
}

bool OpenALRF::MapSearchNode::GetSuccessors(AStarSearch<MapSearchNode>* astarsearch, const MapSearchNode * parent_node) const
{
   int parent_x = -1;
   int parent_y = -1;

   if (parent_node)
   {
      parent_x = parent_node->x;
      parent_y = parent_node->y;
   }


   MapSearchNode NewNode;

   // push each possible move except allowing the search to go backwards

   if ((CurrentSearchMap->GetMapValue(x - 1, y) < OpenALRF::MapValueObstructed)
      && !((parent_x == x - 1) && (parent_y == y))
      )
   {
      NewNode = MapSearchNode(x - 1, y);
      astarsearch->AddSuccessor(NewNode);
   }

   if ((CurrentSearchMap->GetMapValue(x, y - 1) < OpenALRF::MapValueObstructed)
      && !((parent_x == x) && (parent_y == y - 1))
      )
   {
      NewNode = MapSearchNode(x, y - 1);
      astarsearch->AddSuccessor(NewNode);
   }

   if ((CurrentSearchMap->GetMapValue(x + 1, y) < OpenALRF::MapValueObstructed)
      && !((parent_x == x + 1) && (parent_y == y))
      )
   {
      NewNode = MapSearchNode(x + 1, y);
      astarsearch->AddSuccessor(NewNode);
   }


   if ((CurrentSearchMap->GetMapValue(x, y + 1) < OpenALRF::MapValueObstructed)
      && !((parent_x == x) && (parent_y == y + 1))
      )
   {
      NewNode = MapSearchNode(x, y + 1);
      astarsearch->AddSuccessor(NewNode);
   }

   return true;
}

float OpenALRF::MapSearchNode::GetCost(const MapSearchNode & successor) const
{
   return CurrentSearchMap->GetMapValue(x, y);
}

bool OpenALRF::MapSearchNode::IsSameState(const MapSearchNode & rhs) const
{
   return (x == rhs.x) && (y == rhs.y);
}

void OpenALRF::MapSearchNode::PrintNodeInfo() const
{
   char str[100];
   sprintf(str, "(%d,%d)", x, y);

   cout << "Node position : " << str << std::endl;
}

int OpenALRF::MapSearchNode::GetX() const
{
   return this->x;
}

int OpenALRF::MapSearchNode::GetY() const
{
   return this->y;
}

void OpenALRF::SetCurrentSearchMap(IMap *AMap)
{
   CurrentSearchMap = AMap;
}
