#include "SystemLinux.h"

#include <cstdlib>
#include <Jumpropes/Functions.h>

void OpenALRF::SystemLinux::SystemCmd(std::string ACommand)
{
#ifdef GF_OS_WIN32
   std::cout << ACommand << std::endl;
#else
   ::system(ACommand.c_str());
#endif
}

OpenALRF::SystemLinux::SystemLinux() : ISystem()
{
   RebootTriggered = false;
}

void OpenALRF::SystemLinux::RebootNow()
{
   std::string Command = "sudo reboot now";

   SystemCmd(Command.c_str());

   RebootTriggered = true;
}

bool OpenALRF::SystemLinux::HasValidActiveNetwork()
{
   bool HasNetwork = false;

   auto list = Jumpropes::ListNetworkInterfaces();
   for (auto netif : list)
   {
      if (!netif.IP.ip.startsWith_ansi("127.") && !netif.IP.ip.startsWith_ansi("0.") && !netif.IP.ip.startsWith_ansi("169.254."))
      {
         HasNetwork = true;
         break;
      }
   }

   return HasNetwork;
}

void OpenALRF::SystemLinux::RestartNetworkInterface(const std::string AInterfaceName)
{
   std::string Command = "sudo ifdown " + AInterfaceName + " && sudo ifup " + AInterfaceName;

   SystemCmd(Command.c_str());
}

bool OpenALRF::SystemLinux::ShouldQuit()
{
   return RebootTriggered;
}
