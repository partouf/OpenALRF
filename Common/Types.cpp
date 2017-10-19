#include "Types.h"
#include "MemUtils.h"
#include <memory>

bool OpenALRF::operator==(const Command & a, const Command & b)
{
   return (a.Module == b.Module) && (a.Action == b.Action) && (a.ExecutionTime == b.ExecutionTime) && (a.param1 == b.param1) && (a.param2 == b.param2) && (a.param3 == b.param3);
}

bool OpenALRF::operator!=(const Command & a, const Command & b)
{
   return !(a == b);
}

std::ostream & OpenALRF::operator<<(std::ostream & stream, const Command & command)
{
   std::string streambuffer;
   streambuffer << command;
   stream << streambuffer;

   return stream;
}

std::string & OpenALRF::operator<<(std::string & stream, const Command & command)
{
   std::string streambuffer;

   uint32_t cmdlen = 2 + 2 + sizeof(command.param1) + sizeof(command.param2) + sizeof(command.ExecutionTime) + command.param3.length();

   streambuffer.reserve(cmdlen + 4);

   char *buffer = new char[cmdlen + 4];

   buffer[0] = (cmdlen >> 24) & 0xff;
   buffer[1] = (cmdlen >> 16) & 0xff;
   buffer[2] = (cmdlen >> 8) & 0xff;
   buffer[3] = cmdlen & 0xff;

   buffer[4] = (static_cast<int>(command.Module) >> 8) & 0xff;
   buffer[5] = static_cast<int>(command.Module) & 0xff;

   buffer[6] = (static_cast<int>(command.Action) >> 8) & 0xff;
   buffer[7] = static_cast<int>(command.Action) & 0xff;

   buffer[8] = (command.param1 >> 8) & 0xff;
   buffer[9] = command.param1 & 0xff;

   buffer[10] = (command.param2 >> 8) & 0xff;
   buffer[11] = command.param2 & 0xff;

   CopyMem(&command.ExecutionTime, buffer + 12);

   streambuffer.append(buffer, 12 + sizeof(command.ExecutionTime));
   streambuffer.append(command.param3);

   delete[]buffer;

   stream.append(streambuffer);

   return stream;
}

bool OpenALRF::operator==(const OrderedCommand & a, const OrderedCommand & b)
{
   return (a.Type == b.Type) && (a.Order == b.Order) && (a.Cmd == b.Cmd);
}

bool OpenALRF::operator!=(const OrderedCommand & a, const OrderedCommand & b)
{
   return !(a == b);
}

std::ostream & OpenALRF::operator<<(std::ostream & stream, const OrderedCommand & command)
{
   std::string streambuffer;
   streambuffer << command;
   stream << streambuffer;

   return stream;
}

std::string & OpenALRF::operator<<(std::string & stream, const OrderedCommand & command)
{
   std::string streambuffer;

   char buffer[2];
   buffer[0] = (command.Order >> 8) && 0xff;
   buffer[1] = command.Order && 0xff;
   
   streambuffer.append(buffer, 2);

   streambuffer << command.Cmd;

   stream.append(streambuffer);

   return stream;
}



/*
uint32_t cmdlen = (msg[0] << 24) | (msg[1] << 16) | (msg[2] << 8) | msg[3];

if (cmdlen >= 8)
{
   BinCmd.Cmd.Module = static_cast<OpenALRF::Module>(msg[4] << 8 | msg[5]);
   BinCmd.Cmd.Action = static_cast<OpenALRF::Action>(msg[6] << 8 | msg[7]);

   if (cmdlen >= 10)
   {
      BinCmd.Cmd.param1 = static_cast<int16_t>(msg[8] << 8 | msg[9]);
      if (cmdlen >= 12)
      {
         BinCmd.Cmd.param2 = static_cast<int16_t>(msg[10] << 8 | msg[11]);

         BinCmd.Cmd.param3 = "";
         if (cmdlen > 12)
         {
            Groundfloor::String StrParam(sMessage->getPointer(12), cmdlen - 12);
            BinCmd.Cmd.param3.append(StrParam.getValue(), StrParam.getLength());
         }
      }
   }

   skipcount += cmdlen;

   AData->remove(0, skipcount - 1);
}
*/

OpenALRF::Command OpenALRF::Command::Empty()
{
   return Command{OpenALRF::Module::Void, OpenALRF::Action::Void, 0, 0, 0, ""};
}
