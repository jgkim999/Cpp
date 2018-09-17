#include "stdafx.h"
#include <iostream>
#include "Message.h"

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

	serialize::Message reader(writer.Data(), writer.Length());
	{
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
    return 0;
}