#pragma once

#include <string>

struct SerialStruct
{
  int a;
  float b;
  double c;
  std::string d;
  std::wstring e;
};

namespace serialize {

class Message;
Message& operator << (Message& msg, const SerialStruct& value);
Message& operator >> (Message& msg, SerialStruct& value);
}