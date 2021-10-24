#pragma once
#include "IInputDataStreamDecorator.h"
#include "CodeDecodeGenerator.h"

class DecodeStreamDecorator : public IInputDataStreamDecorator
{
public:
	DecodeStreamDecorator(InputStreamPtr&& stream, int seed)
		: IInputDataStreamDecorator(move(stream))
	{
		CodeDecodeGenerator gen;
		gen.Generate(seed);
		m_decodeMap = gen.GetDecodeMap();
	}

	bool IsEOF() const override
	{
		return IInputDataStreamDecorator::IsEOF();
	}

	uint8_t ReadByte() override
	{
		return m_decodeMap[IInputDataStreamDecorator::ReadByte()];
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
	{
		auto data = static_cast<uint8_t*>(dstBuffer);
		try
		{
			for (std::streamsize i = 0; i < size; i++)
			{
				data[i] = ReadByte();
			}
		}
		catch (...)
		{
			throw std::ios_base::failure("Failed to read");
		}
		return size;
	}

private:
	std::unordered_map<uint8_t, uint8_t> m_decodeMap;
};