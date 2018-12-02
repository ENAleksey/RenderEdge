#include "Buffer.h"

BUFFER::BUFFER()
	: buffer_()
{
}

BUFFER::BUFFER(const std::string& CopyString)
	: buffer_(CopyString)
{
}

BUFFER::~BUFFER()
{
}


void BUFFER::Resize(size_t NewSize)
{
	buffer_.resize(NewSize);
}


unsigned char* BUFFER::GetData(size_t Index)
{
	return const_cast<unsigned char*>((const unsigned char*)buffer_.data()) + Index;
}

const unsigned char* BUFFER::GetData(size_t Index) const
{
	return (const unsigned char*)buffer_.data() + Index;
}

size_t BUFFER::GetSize() const
{
	return buffer_.size();
}


char& BUFFER::operator [](size_t Index)
{
	return buffer_[Index];
}

std::string const& BUFFER::Buf() const 
{
	return buffer_;
};