#include "stdafx.h"
#include "Message.h"

namespace serialize
{
	Message::Message()
	{
		MakeBuffer(kDefaultBufferSize);
	}

	Message::Message(const Message& message)
	{
		MakeBuffer(message.Capacity());
		memcpy_s(buffer_, buffer_size_, message.Data(), message.Size());
	}

	Message::Message(size_t buffer_size)
	{
		MakeBuffer(buffer_size);
	}

	Message::Message(const char* data, size_t size)
	{
		MakeBuffer(size);
		memcpy_s(buffer_, buffer_size_, data, size);
	}

	Message::~Message()
	{
		delete[] buffer_;
	}

	size_t Message::Capacity() const
	{
		return buffer_size_;
	}

	size_t Message::Size() const
	{
		return write_offset_;
	}

	size_t Message::Length() const
	{
		return Size();
	}

	const char* Message::Data() const
	{
		return buffer_;
	}

	void Message::Clear()
	{
		write_offset_ = 0;
		read_offset_ = 0;
	}

	void Message::MakeBuffer(size_t buffer_size)
	{
		if (buffer_size % kAlignment != 0)
			buffer_size = (buffer_size / kAlignment + 1) * kAlignment;

		buffer_ = new char[buffer_size];
		buffer_size_ = buffer_size;
	}

	void Message::AdjustWriteBuffer(size_t size)
	{
		size_t need_size = write_offset_ + size;
		if (need_size < buffer_size_)
			return;

		buffer_size_ = need_size * 2;
		if (buffer_size_ % kAlignment != 0)
			buffer_size_ = (buffer_size_ / kAlignment + 1) * kAlignment;

		char* new_buffer = new char[buffer_size_];
		memcpy_s(new_buffer, buffer_size_, buffer_, write_offset_);
		delete[] buffer_;
		buffer_ = new_buffer;
	}

	void Message::Write(int8_t value)
	{
		AdjustWriteBuffer(sizeof(value));
		memcpy_s(buffer_ + write_offset_, buffer_size_ - write_offset_, &value, sizeof(value));
		write_offset_ += sizeof(value);
	}

	void Message::Read(int8_t& value)
	{
		memcpy_s(&value, sizeof(value), buffer_ + read_offset_, sizeof(value));
		read_offset_ += sizeof(value);
	}

	void Message::Write(int16_t value)
	{
		AdjustWriteBuffer(sizeof(value));
		memcpy_s(buffer_ + write_offset_, buffer_size_ - write_offset_, &value, sizeof(value));
		write_offset_ += sizeof(value);
	}

	void Message::Read(int16_t& value)
	{
		memcpy_s(&value, sizeof(value), buffer_ + read_offset_, sizeof(value));
		read_offset_ += sizeof(value);
	}

	void Message::Write(int32_t value)
	{
		AdjustWriteBuffer(sizeof(value));
		memcpy_s(buffer_ + write_offset_, buffer_size_ - write_offset_, &value, sizeof(value));
		write_offset_ += sizeof(value);
	}

	void Message::Read(int32_t& value)
	{
		memcpy_s(&value, sizeof(value), buffer_ + read_offset_, sizeof(value));
		read_offset_ += sizeof(value);
	}

	void Message::Write(int64_t value)
	{
		AdjustWriteBuffer(sizeof(value));
		memcpy_s(buffer_ + write_offset_, buffer_size_ - write_offset_, &value, sizeof(value));
		write_offset_ += sizeof(value);
	}

	void Message::Read(int64_t& value)
	{
		memcpy_s(&value, sizeof(value), buffer_ + read_offset_, sizeof(value));
		read_offset_ += sizeof(value);
	}

	void Message::Write(uint8_t value)
	{
		AdjustWriteBuffer(sizeof(value));
		memcpy_s(buffer_ + write_offset_, buffer_size_ - write_offset_, &value, sizeof(value));
		write_offset_ += sizeof(value);
	}

	void Message::Read(uint8_t& value)
	{
		memcpy_s(&value, sizeof(value), buffer_ + read_offset_, sizeof(value));
		read_offset_ += sizeof(value);
	}

	void Message::Write(uint16_t value)
	{
		AdjustWriteBuffer(sizeof(value));
		memcpy_s(buffer_ + write_offset_, buffer_size_ - write_offset_, &value, sizeof(value));
		write_offset_ += sizeof(value);
	}

	void Message::Read(uint16_t& value)
	{
		memcpy_s(&value, sizeof(value), buffer_ + read_offset_, sizeof(value));
		read_offset_ += sizeof(value);
	}

	void Message::Write(uint32_t value)
	{
		AdjustWriteBuffer(sizeof(value));
		memcpy_s(buffer_ + write_offset_, buffer_size_ - write_offset_, &value, sizeof(value));
		write_offset_ += sizeof(value);
	}

	void Message::Read(uint32_t& value)
	{
		memcpy_s(&value, sizeof(value), buffer_ + read_offset_, sizeof(value));
		read_offset_ += sizeof(value);
	}

	void Message::Write(uint64_t value)
	{
		AdjustWriteBuffer(sizeof(value));
		memcpy_s(buffer_ + write_offset_, buffer_size_ - write_offset_, &value, sizeof(value));
		write_offset_ += sizeof(value);
	}

	void Message::Read(uint64_t& value)
	{
		memcpy_s(&value, sizeof(value), buffer_ + read_offset_, sizeof(value));
		read_offset_ += sizeof(value);
	}

	void Message::Write(float value)
	{
		AdjustWriteBuffer(sizeof(value));
		memcpy_s(buffer_ + write_offset_, buffer_size_ - write_offset_, &value, sizeof(value));
		write_offset_ += sizeof(value);
	}

	void Message::Read(float& value)
	{
		memcpy_s(&value, sizeof(value), buffer_ + read_offset_, sizeof(value));
		read_offset_ += sizeof(value);
	}

	void Message::Write(double value)
	{
		AdjustWriteBuffer(sizeof(value));
		memcpy_s(buffer_ + write_offset_, buffer_size_ - write_offset_, &value, sizeof(value));
		write_offset_ += sizeof(value);
	}

	void Message::Read(double& value)
	{
		memcpy_s(&value, sizeof(value), buffer_ + read_offset_, sizeof(value));
		read_offset_ += sizeof(value);
	}

	void Message::Write(bool value)
	{
		AdjustWriteBuffer(sizeof(int8_t));
		memcpy_s(buffer_ + write_offset_, buffer_size_ - write_offset_, &value, sizeof(int8_t));
		write_offset_ += sizeof(int8_t);
	}

	void Message::Read(bool& value)
	{
		int8_t temp;
		memcpy_s(&temp, sizeof(int8_t), buffer_ + read_offset_, sizeof(int8_t));
		read_offset_ += sizeof(int8_t);
		value = temp != 0 ? true : false;
	}

	void Message::Write(const std::string& str)
	{
		Write((uint32_t)str.size());

		size_t str_size = str.size();
		AdjustWriteBuffer(str_size);
		memcpy_s(buffer_ + write_offset_, buffer_size_ - write_offset_, str.c_str(), str_size);
		write_offset_ += str_size;
	}

	void Message::Read(std::string& str)
	{
		uint32_t str_size = 0;
		Read(str_size);
		str.reserve(str_size);
		str.assign(buffer_ + read_offset_, str_size);
		read_offset_ += str_size;
	}

	void Message::Write(const std::wstring& str)
	{
		Write((uint32_t)str.size());

		size_t str_size = str.size() * sizeof(wchar_t);
		AdjustWriteBuffer(str_size);
		memcpy_s(buffer_ + write_offset_, buffer_size_ - write_offset_, str.c_str(), str_size);
		write_offset_ += str_size;
	}

	void Message::Read(std::wstring& str)
	{
		uint32_t str_size = 0;
		Read(str_size);
		str.reserve(str_size);
		str.assign((const wchar_t*)(buffer_ + read_offset_), str_size);
		read_offset_ += (str_size * sizeof(wchar_t));
	}

	Message& operator << (Message& msg, int8_t value)
	{
		msg.Write(value);
		return msg;
	}

	Message& operator >> (Message& msg, int8_t& value)
	{
		msg.Read(value);
		return msg;
	}

	Message& operator << (Message& msg, int16_t value)
	{
		msg.Write(value);
		return msg;
	}

	Message& operator >> (Message& msg, int16_t& value)
	{
		msg.Read(value);
		return msg;
	}

	Message& operator << (Message& msg, int32_t value)
	{
		msg.Write(value);
		return msg;
	}

	Message& operator >> (Message& msg, int32_t& value)
	{
		msg.Read(value);
		return msg;
	}

	Message& operator << (Message& msg, int64_t value)
	{
		msg.Write(value);
		return msg;
	}

	Message& operator >> (Message& msg, int64_t& value)
	{
		msg.Read(value);
		return msg;
	}

	Message& operator << (Message& msg, uint8_t value)
	{
		msg.Write(value);
		return msg;
	}

	Message& operator >> (Message& msg, uint8_t& value)
	{
		msg.Read(value);
		return msg;
	}

	Message& operator << (Message& msg, uint16_t value)
	{
		msg.Write(value);
		return msg;
	}

	Message& operator >> (Message& msg, uint16_t& value)
	{
		msg.Read(value);
		return msg;
	}

	Message& operator << (Message& msg, uint32_t value)
	{
		msg.Write(value);
		return msg;
	}

	Message& operator >> (Message& msg, uint32_t& value)
	{
		msg.Read(value);
		return msg;
	}

	Message& operator << (Message& msg, uint64_t value)
	{
		msg.Write(value);
		return msg;
	}

	Message& operator >> (Message& msg, uint64_t& value)
	{
		msg.Read(value);
		return msg;
	}

	Message& operator << (Message& msg, const std::string& value)
	{
		msg.Write(value);
		return msg;
	}

	Message& operator >> (Message& msg, std::string& value)
	{
		msg.Read(value);
		return msg;
	}

	Message& operator << (Message& msg, const std::wstring& value)
	{
		msg.Write(value);
		return msg;
	}

	Message& operator >> (Message& msg, std::wstring& value)
	{
		msg.Read(value);
		return msg;
	}

	Message& operator << (Message& msg, bool value)
	{
		msg.Write(value);
		return msg;
	}

	Message& operator >> (Message& msg, bool& value)
	{
		msg.Read(value);
		return msg;
	}

	Message& operator << (Message& msg, float value)
	{
		msg.Write(value);
		return msg;
	}

	Message& operator >> (Message& msg, float& value)
	{
		msg.Read(value);
		return msg;
	}

	Message& operator << (Message& msg, double value)
	{
		msg.Write(value);
		return msg;
	}

	Message& operator >> (Message& msg, double& value)
	{
		msg.Read(value);
		return msg;
	}
}