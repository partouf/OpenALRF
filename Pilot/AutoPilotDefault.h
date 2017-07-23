#pragma once

#include "AutoPilot.h"
#include "RemotePilot.h"
#include "../World/AStarMapNode.h"
#include "../World/MapTypes.h"
#include "../Command/CommandQueue.h"

namespace OpenALRF
{
   class AutoPilotDefault : public IAutoPilot
   {
   private:
      OpenALRF::degrees_t CurrentAngle;
      IMapProvider *MapProvider;
      ICommandQueue *CommandQueue;

      OpenALRF::degrees_t MakeCommandsFromMapSearchDifference(const OpenALRF::MapSearchNode *ANodeCurrent, const OpenALRF::MapSearchNode *ANodeNext, const OpenALRF::degrees_t ACurrentAngle);
      void findSolutionForMap(const std::string AInMapFile);

      void FullRoute(const OpenALRF::IMapReader * AMap, OpenALRF::MapSearchNode &StartNode, OpenALRF::MapSearchNode &EndNode);
   public:
      AutoPilotDefault(IMapProvider *AMapProvider, ICommandQueue * ACommandQueue);

      void IdleStep(const OpenALRF::IMapReader * AMap, OpenALRF::MapSearchNode &StartNode, OpenALRF::MapSearchNode &EndNode);
   };
}