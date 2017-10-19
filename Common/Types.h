#pragma once

#include <cstdint>
#include <string>

namespace OpenALRF
{
   typedef int64_t timestamp_t;

   enum class Status { Stopped = 0, Running = 1, Waiting = 2 };

   enum class Module { Void = 0, RemotePilot = 1, AutoPilot = 2, Camera = 3, Fancy = 5, System = 9 };
   
   enum class Action {
      Void = 0,
      RemotePilotForward = 11, RemotePilotBackward = 12, RemotePilotLeft = 13, RemotePilotRight = 14, RemotePilotStop = 15,
      CameraCapture = 31,
      FancyBlink1 = 51, FancyBlink2 = 51,
      SystemReboot = 91, SystemRestartNetIF = 92, SystemInfoReport = 93, SystemResume = 94, SystemWait = 95, SystemStop = 96
   };

   enum class Order {
      Any = 0,
      Start = 1,
      Stop = 2
   };

   struct Command
   {
      Module Module;
      Action Action;
      timestamp_t ExecutionTime;
      int16_t param1;
      int16_t param2;
      std::string param3;

      static Command Empty();
   };
   bool operator ==(const Command &a, const Command &b);
   bool operator !=(const Command &a, const Command &b);
   std::ostream& operator<< (std::ostream& stream, const Command& command);
   std::string& operator<< (std::string& stream, const Command& command);

   struct OrderedCommand
   {
      int16_t Order;
      OpenALRF::Order Type;
      Command Cmd;
   };
   bool operator ==(const OrderedCommand &a, const OrderedCommand &b);
   bool operator !=(const OrderedCommand &a, const OrderedCommand &b);
   std::ostream& operator<< (std::ostream& stream, const OrderedCommand& command);
   std::string& operator<< (std::string& stream, const OrderedCommand& command);
};
