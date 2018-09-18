#pragma once

#include <cstdint>
#include <algorithm>
#include <string>

namespace serialize
{
	class Message
	{
		const size_t kAlignment = 32;
		const size_t kDefaultBufferSize = 1024;
	public:
		Message();
		Message(const Message& message);
		Message(size_t buffer_size);
		Message(const char* data, size_t size);
		~Message();
		size_t Capacity() const;
		size_t Size() const;
		size_t Length() const;
		const char* Data() const;
		void Clear();
	private:
		void MakeBuffer(size_t buffer_size);
		void AdjustWriteBuffer(size_t size);
		Message& operator= (const Message&) = delete;
	public:
		void Write(int8_t value);
		void Read(int8_t& value);
		void Write(int16_t value);
		void Read(int16_t& value);
		void Write(int32_t value);
		void Read(int32_t& value);
		void Write(int64_t value);
		void Read(int64_t& value);
		void Write(uint8_t value);
		void Read(uint8_t& value);
		void Write(uint16_t value);
		void Read(uint16_t& value);
		void Write(uint32_t value);
		void Read(uint32_t& value);
		void Write(uint64_t value);
		void Read(uint64_t& value);
		void Write(float value);
		void Read(float& value);
		void Write(double value);
		void Read(double& value);
		void Write(bool value);
		void Read(bool& value);
		void Write(const std::string& str);
		void Read(std::string& str);
		void Write(const std::wstring& str);
		void Read(std::wstring& str);
	private:
		size_t write_offset_ = 0;
		size_t read_offset_ = 0;
		size_t buffer_size_;
		char* buffer_;
	};

	Message& operator << (Message& msg, int8_t value);
	Message& operator >> (Message& msg, int8_t& value);
	Message& operator << (Message& msg, int16_t value);
	Message& operator >> (Message& msg, int16_t& value);
	Message& operator << (Message& msg, int32_t value);
	Message& operator >> (Message& msg, int32_t& value);
	Message& operator << (Message& msg, int64_t value);
	Message& operator >> (Message& msg, int64_t& value);
	Message& operator << (Message& msg, uint8_t value);
	Message& operator >> (Message& msg, uint8_t& value);
	Message& operator << (Message& msg, uint16_t value);
	Message& operator >> (Message& msg, uint16_t& value);
	Message& operator << (Message& msg, uint32_t value);
	Message& operator >> (Message& msg, uint32_t& value);
	Message& operator << (Message& msg, uint64_t value);
	Message& operator >> (Message& msg, uint64_t& value);
	Message& operator << (Message& msg, const std::string& value);
	Message& operator >> (Message& msg, std::string& value);
	Message& operator << (Message& msg, const std::wstring& value);
	Message& operator >> (Message& msg, std::wstring& value);
	Message& operator << (Message& msg, bool value);
	Message& operator >> (Message& msg, bool& value);
	Message& operator << (Message& msg, float value);
	Message& operator >> (Message& msg, float& value);
	Message& operator << (Message& msg, double value);
	Message& operator >> (Message& msg, double& value);
}