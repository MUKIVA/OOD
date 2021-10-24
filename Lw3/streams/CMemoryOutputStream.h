#pragma once
#include "IOutputDataStream.h"
#include <queue>


class CMemoryOutputStream : public IOutputDataStream
{
public:
	std::queue<uint8_t> GetMemory() const
	{
		return m_memory;
	}

	void WriteByte(uint8_t data) override
	{
		try
		{
			m_memory.push(data);
		}
		catch (...)
		{
			throw std::ios_base::failure("Failed to allocate memory");
		}
	}

	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		try
		{
			uint8_t* data = (uint8_t*)srcData;
			for (std::streamsize i = 0; i < size; ++i)
			{
				m_memory.push(*(data + i));
			}
		}
		catch (...)
		{
			throw std::ios_base::failure("Failed to allocate memory");
		}
	}

private:
	std::queue<uint8_t> m_memory;
};