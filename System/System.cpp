#include "System.h"

OpenALRF::status_t OpenALRF::ISystem::CurrentStatus() const
{
   return SuggestedStatus;
}

void OpenALRF::ISystem::ChangeStatus(OpenALRF::status_t ANewStatus)
{
   SuggestedStatus = ANewStatus;
}
