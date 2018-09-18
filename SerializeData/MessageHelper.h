#pragma once

#include <array>
#include <vector>
#include "Message.h"

namespace serialize {

	//! array write.
	template<typename T, size_t N>
	Message& operator << (Message& msg, const std::array<T, N>& value)
	{
		msg.Write((uint32_t)value.size());
		for (size_t i = 0, j = value.size(); i < j; ++i)
			msg << value[i];
		return msg;
	}

	//! array read.
	template<typename T, size_t N>
	Message& operator >> (Message& msg, std::array<T, N>& value)
	{
		uint32_t array_size = 0;
		msg >> array_size;
		// if (value.size() != array_size)
		// throw exception or error.
		for (uint32_t i = 0; i < array_size; ++i)
			msg >> value[i];
		return msg;
	}

	//! vector write.
	template<typename T>
	Message& operator << (Message& msg, const std::vector<T>& value)
	{
		msg.Write((uint32_t)value.size());
		for (size_t i = 0, j = value.size(); i < j; ++i)
			msg << value[i];
		return msg;
	}

	//! vector read.
	template<typename T>
	Message& operator >> (Message& msg, std::vector<T>& value)
	{
		uint32_t array_size = 0;
		msg >> array_size;
		value.reserve(array_size);
		for (uint32_t i = 0; i < array_size; ++i)
		{
			T elmt;
			msg >> elmt;
			value.emplace_back(elmt);
		}
		return msg;
	}
}