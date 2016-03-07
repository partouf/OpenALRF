#include "SystemLinux.h"

#include <cstdlib>

OpenALRF::SystemLinux::SystemLinux() : ISystem()
{
}

void OpenALRF::SystemLinux::RebootNow()
{
   system("sudo reboot now");
}
