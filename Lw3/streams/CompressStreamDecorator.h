#pragma once
#include "IOutputDataStreamDecorator.h"


class CompressStreamDecorator : public IOutputDataStreamDecorator
{
public:
	CompressStreamDecorator(OutputStreamPtr&& stream)
		: IOutputDataStreamDecorator(move(stream))
	{
	}

	void WriteByte(uint8_t data) override
	{
		if (m_count == 0)
		{
			++m_count;
			m_currentByte = data;
			return;
		}

		if (m_currentByte != data || m_count >= 255)
		{
			IOutputDataStreamDecorator::WriteByte(m_count);
			IOutputDataStreamDecorator::WriteByte(m_currentByte);
			m_count = 1;
			m_currentByte = data;
			return;
		}
		++m_count;
	}

	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		auto data = static_cast<const uint8_t*>(srcData);
		try
		{
			for (std::streamsize i = 0; i < size; ++i)
			{
				WriteByte(data[i]);
			}
			IOutputDataStreamDecorator::WriteByte(m_count);
			IOutputDataStreamDecorator::WriteByte(m_currentByte);
		}
		catch (...)
		{
			throw std::ios_base::failure("Fail to write");
		}
	}

private:
	uint8_t m_count = 0;
	uint8_t m_currentByte = 0;
};