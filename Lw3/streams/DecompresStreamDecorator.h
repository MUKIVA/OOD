#pragma once
#include "IInputDataStreamDecorator.h"



class DecompresStreamDecorator : public IInputDataStreamDecorator
{
public:
	DecompresStreamDecorator(InputStreamPtr&& stream)
		: IInputDataStreamDecorator(move(stream))
	{
	}

	bool IsEOF() const override
	{
		return IInputDataStreamDecorator::IsEOF();
	}

	uint8_t ReadByte() override
	{
		if (m_count == 0)
		{
			m_count = IInputDataStreamDecorator::ReadByte();
			m_currentByte = IInputDataStreamDecorator::ReadByte();
			m_realReadByte += 2;
		}
		--m_count;
		return m_currentByte;
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
	{
		auto data = static_cast<uint8_t*>(dstBuffer);
		try
		{
			for (std::streamsize i = 0; i < size; ++i)
			{
				data[i] = ReadByte();
			}
		}
		catch (...)
		{
			throw std::ios_base::failure("Failed to read block");
		}
		std::streamsize tmp = 0;
		std::swap(tmp, m_realReadByte);
		return tmp;
	}

private:
	uint8_t m_count = 0;
	uint8_t m_currentByte = 0;
	std::streamsize m_realReadByte = 0;
};