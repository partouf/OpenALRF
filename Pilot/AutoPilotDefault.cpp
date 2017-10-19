#include "AutoPilotDefault.h"
#include "../World/MapUtils.h"
#include "../World/Map.h"
#include "../World/MapRoute.h"

OpenALRF::degrees_t OpenALRF::AutoPilotDefault::MakeCommandsFromMapSearchDifference(const OpenALRF::MapSearchNode * ANodeCurrent, const OpenALRF::MapSearchNode * ANodeNext, const OpenALRF::degrees_t ACurrentAngle)
{
   int16_t distance = static_cast<int16_t>(MapUtils::GetDistanceBetweenMapSearchNodes(ANodeCurrent, ANodeNext) * 60);
   int angle = MapUtils::GetAngleBetweenMapSearchNodes(ANodeCurrent, ANodeNext);

   OpenALRF::degrees_t NewAngle = ACurrentAngle;

   if (angle == -1)
   {
      // do nothing
   }
   else if (angle == 180)
   {
      // best to just go backwards instead of turning
      CommandQueue->Add({ OpenALRF::Module::RemotePilot, OpenALRF::Action::RemotePilotBackward, distance });
      NewAngle = 0;
   }
   else if (angle == 0)
   {
      CommandQueue->Add({ OpenALRF::Module::RemotePilot, OpenALRF::Action::RemotePilotForward, distance });
      NewAngle = 0;
   }
   else
   {
      NewAngle -= ACurrentAngle;

      if (NewAngle > 180)
      {
         CommandQueue->Add({ OpenALRF::Module::RemotePilot, OpenALRF::Action::RemotePilotLeft, static_cast<int16_t>(180 - NewAngle) });
      }
      else if (NewAngle > 0)
      {
         CommandQueue->Add({ OpenALRF::Module::RemotePilot, OpenALRF::Action::RemotePilotRight, NewAngle });
      }

      CommandQueue->Add({ OpenALRF::Module::RemotePilot, OpenALRF::Action::RemotePilotForward, distance });
   }

   return NewAngle;
}

OpenALRF::AutoPilotDefault::AutoPilotDefault(IMapProvider * AMapProvider, ICommandQueue * ACommandQueue) : IAutoPilot()
{
   this->MapProvider = AMapProvider;
   this->CommandQueue = ACommandQueue;
}

void OpenALRF::AutoPilotDefault::IdleStep(const OpenALRF::IMapReader * AMap, OpenALRF::MapSearchNode &StartNode, OpenALRF::MapSearchNode &EndNode)
{
   MapRoute Route(AMap);
   Route.DoSearch(StartNode, EndNode);

   OpenALRF::MapSearchNode *previousnode = &StartNode;

   auto node = Route.GetNextSolutionNode();
   if (!node) return;

   CurrentAngle = MakeCommandsFromMapSearchDifference(previousnode, node, CurrentAngle);
}

void OpenALRF::AutoPilotDefault::FullRoute(const OpenALRF::IMapReader * AMap, OpenALRF::MapSearchNode &StartNode, OpenALRF::MapSearchNode &EndNode)
{
   MapRoute Route(AMap);
   Route.DoSearch(StartNode, EndNode);

   OpenALRF::MapSearchNode *previousnode = &StartNode;

   int steps = 0;
   for (;; )
   {
      auto node = Route.GetNextSolutionNode();
      if (!node) break;

      CurrentAngle = MakeCommandsFromMapSearchDifference(previousnode, node, CurrentAngle);
      previousnode = node;

      steps++;
   };
}

void OpenALRF::AutoPilotDefault::findSolutionForMap(const std::string AInMapFile)
{
   OpenALRF::Map20x20m map(AInMapFile);
   OpenALRF::MapSearchNode StartNode(10, 20);
   OpenALRF::MapSearchNode EndNode(10, 0);

   try
   {
      FullRoute(&map, StartNode, EndNode);
   }
   catch (const SolutionNotFound&)
   {
   }
}
