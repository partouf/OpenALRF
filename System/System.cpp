#include "System.h"

OpenALRF::status_t OpenALRF::ISystem::CurrentStatus()
{
   return SuggestedStatus;
}

void OpenALRF::ISystem::ChangeStatus(OpenALRF::status_t ANewStatus)
{
   SuggestedStatus = ANewStatus;
}
