#include "stdafx.h"
#include <iostream>
#include "Message.h"
#include "MessageHelper.h"
#include "SerialStruct.h"

int main()
{
  serialize::Message writer;
  {
    int8_t a = 10;
    int16_t b = 11;
    int32_t c = 12;
    int64_t d = 13;
    int64_t e = 14;
    int64_t f = 15;
    std::string g("Hello world");
    std::wstring h(L"WSTRING HELLO WORLD");
    bool i = true;
    bool j = false;
    float k = 3.14f;
    double l = 4.13;
    writer << a << b << c << d << e << f << g << h << i << j << k << l;
    std::cout << "capacity:" << writer.Capacity() << " size:" << writer.Size() << std::endl;
  }
  {
    serialize::Message reader(writer.Data(), writer.Length());
    int8_t a;
    int16_t b;
    int32_t c;
    int64_t d;
    int64_t e;
    int64_t f;
    std::string g;
    std::wstring h;
    bool i;
    bool j;
    float k;
    double l;
    reader >> a >> b >> c >> d >> e >> f >> g >> h >> i >> j >> k >> l;
  }
  {
    serialize::Message reader(writer);
    int8_t a;
    int16_t b;
    int32_t c;
    int64_t d;
    int64_t e;
    int64_t f;
    std::string g;
    std::wstring h;
    bool i;
    bool j;
    float k;
    double l;
    reader >> a >> b >> c >> d >> e >> f >> g >> h >> i >> j >> k >> l;
  }
  {
    // struct.
    SerialStruct wsst;
    wsst.a = 1;
    wsst.b = 2.3f;
    wsst.c = 4.5;
    wsst.d = "sst d";
    wsst.e = L"sst e";

    serialize::Message wmsg;
    wmsg << wsst;

    SerialStruct rsst;
    serialize::Message rmsg(wmsg);
    rmsg >> rsst;
  }
  {
    // array
    SerialStruct wsst;
    wsst.a = 1;
    wsst.b = 2.3f;
    wsst.c = 4.5;
    wsst.d = "sst d";
    wsst.e = L"sst e";

    std::array<SerialStruct, 5> warray;
    warray[0] = wsst;
    warray[1] = wsst;
    warray[2] = wsst;
    warray[3] = wsst;
    warray[4] = wsst;

    serialize::Message wmsg;
    wmsg << warray;

    std::array<SerialStruct, 5> rarray;
    serialize::Message rmsg(wmsg);
    rmsg >> rarray;
  }
  {
    // vector
    SerialStruct wsst;
    wsst.a = 1;
    wsst.b = 2.3f;
    wsst.c = 4.5;
    wsst.d = "sst d";
    wsst.e = L"sst e";

    std::vector<SerialStruct> wvector;
    for (size_t i = 0; i < 100; ++i)
      wvector.emplace_back(wsst);

    serialize::Message wmsg;
    wmsg << wvector;

    std::vector<SerialStruct> rvector;
    serialize::Message rmsg(wmsg);
    rmsg >> rvector;
  }
  return 0;
}