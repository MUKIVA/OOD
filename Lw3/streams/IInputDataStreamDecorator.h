#pragma once
#include "IInputDataStream.h"


class IInputDataStreamDecorator : public IInputDataStream
{
public:
	IInputDataStreamDecorator(InputStreamPtr&& inputStream)
		: m_inputStream(move(inputStream))
	{
	}

	bool IsEOF() const override
	{
		return m_inputStream->IsEOF();
	}

	uint8_t ReadByte() override
	{
		return m_inputStream->ReadByte();
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
	{
		return m_inputStream->ReadBlock(dstBuffer, size);
	}

private:
	InputStreamPtr m_inputStream;
};