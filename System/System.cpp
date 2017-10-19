#include "System.h"

OpenALRF::Status OpenALRF::ISystem::CurrentStatus() const
{
   return SuggestedStatus;
}

void OpenALRF::ISystem::ChangeStatus(OpenALRF::Status ANewStatus)
{
   SuggestedStatus = ANewStatus;
}
