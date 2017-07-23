#pragma once

#include "AStarMapNode.h"
#include "MapTypes.h"

namespace OpenALRF
{
   class SolutionNotFound : public std::runtime_error
   {
   public:
      SolutionNotFound(const char *AMessage) : std::runtime_error(AMessage)
      {
      }
   };

   class MapRoute
   {
   private:
      AStarSearch<OpenALRF::MapSearchNode> Searcher;
      const IMapReader *CurrentMap;
      int SearchState;
      degrees_t CurrentAngle;
   public:
      MapRoute(const OpenALRF::IMapReader *AMap);
      ~MapRoute();

      void DoSearch(OpenALRF::MapSearchNode &StartNode, OpenALRF::MapSearchNode &EndNode);

      OpenALRF::MapSearchNode *GetNextSolutionNode();
   };
}