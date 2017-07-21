#include "MapRoute.h"

void OpenALRF::MapRoute::DoSearch(OpenALRF::MapSearchNode &StartNode, OpenALRF::MapSearchNode &EndNode)
{
   OpenALRF::SetCurrentSearchMap(CurrentMap);

   Searcher.SetStartAndGoalStates(StartNode, EndNode);

   do
   {
      SearchState = Searcher.SearchStep();
   } while (SearchState == STLAStar::SEARCH_STATE_SEARCHING);
}

OpenALRF::MapRoute::MapRoute(const OpenALRF::IMapReader *AMap)
{
   this->CurrentMap = AMap;
   this->SearchState = STLAStar::SEARCH_STATE_NOT_INITIALISED;
}

OpenALRF::MapRoute::~MapRoute()
{
   if (SearchState == STLAStar::SEARCH_STATE_SUCCEEDED)
   {
      Searcher.FreeSolutionNodes();
   }

   Searcher.EnsureMemoryFreed();
}

OpenALRF::MapSearchNode * OpenALRF::MapRoute::GetNextSolutionNode()
{
   return Searcher.GetSolutionNext();
}
