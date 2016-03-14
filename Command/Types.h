#pragma once

#include <cstdint>
#include <string>

namespace OpenALRF
{
   enum module_t { modVoid = 0, modRemotePilot = 1, modAutoPilot = 2, modCamera = 3, modSystem = 9 };
   
   enum action_t {
      actVoid = 0,
      actSystemReboot = 1, actSystemRestartNetIF = 2, actSystemInfoReport = 3,
      actRemotePilotForward = 11, actRemotePilotBackward = 12, actRemotePilotLeft = 13, actRemotePilotRight = 14, actRemotePilotStop = 15,
      actCameraCapture = 21
   };

   struct Command
   {
      module_t Module;
      action_t Action;
      int16_t param1;
      int16_t param2;
      std::string param3;
   };
};
