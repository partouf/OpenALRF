#include "SystemLinux.h"

#include <cstdlib>
#include <iostream>

void OpenALRF::SystemLinux::SystemCmd(std::string ACommand)
{
#ifdef GF_OS_WIN32
   std::cout << ACommand << std::endl;
#else
   std::cout << ACommand << std::endl;
   ::system(ACommand.c_str());
#endif
}

OpenALRF::SystemLinux::SystemLinux() : ISystem()
{
   RebootTriggered = false;
}

void OpenALRF::SystemLinux::RebootNow()
{
   std::string Command = "reboot now";

   SystemCmd(Command.c_str());

   RebootTriggered = true;
}

void OpenALRF::SystemLinux::RestartNetworkInterface(const std::string AInterfaceName)
{
   std::string Command = "ifdown " + AInterfaceName + " && ifup " + AInterfaceName;

   SystemCmd(Command.c_str());
}

bool OpenALRF::SystemLinux::ShouldQuit()
{
   return RebootTriggered;
}
