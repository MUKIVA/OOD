#pragma once
#include "IOutputDataStream.h"

class IOutputDataStreamDecorator : public IOutputDataStream
{
public:
	IOutputDataStreamDecorator(OutputStreamPtr&& outStream)
		: m_outStream(move(outStream))
	{
	}

	void WriteByte(uint8_t data) override
	{
		m_outStream->WriteByte(data);
	}

	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		m_outStream->WriteBlock(srcData, size);
	}

private:
	OutputStreamPtr m_outStream;
};