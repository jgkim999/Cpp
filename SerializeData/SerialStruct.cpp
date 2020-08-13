#include "stdafx.h"
#include "SerialStruct.h"
#include "Message.h"

namespace serialize {

Message& operator << (Message& msg, const SerialStruct& value)
{
  msg << value.a;
  msg << value.b;
  msg << value.c;
  msg << value.d;
  msg << value.e;
  return msg;
}

Message& operator >> (Message& msg, SerialStruct& value)
{
  msg >> value.a;
  msg >> value.b;
  msg >> value.c;
  msg >> value.d;
  msg >> value.e;
  return msg;
}
} // namespace serialize