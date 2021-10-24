#pragma once
#include "IInputDataStream.h"
#include <queue>

class CMemoryInputStream : public IInputDataStream
{
public:
	CMemoryInputStream(std::queue<uint8_t> const& memory)
		: m_memory(memory)
	{
	}

	bool IsEOF() const override
	{
		return m_memory.empty() ? true : false;
	}

	uint8_t ReadByte() override
	{
		if (IsEOF())
		{
			throw std::ios_base::failure("Failed to read");
		}

		uint8_t byte = m_memory.front();
		m_memory.pop();
		return byte;
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
	{
		try
		{
			uint8_t* data = (uint8_t*)dstBuffer;
			for (std::streamsize i = 0; i < size; ++i)
			{
				*(data + i) = m_memory.front();
				m_memory.pop();
			}
		}
		catch (...)
		{
			throw std::ios_base::failure("Failed to read");
		}

		return 0;
	}

private:
	std::queue<uint8_t> m_memory;
};