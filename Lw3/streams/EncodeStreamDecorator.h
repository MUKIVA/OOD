#pragma once
#include "IOutputDataStreamDecorator.h"
#include "CodeDecodeGenerator.h"
#include <unordered_map>

class EncodeStreamDecorator : public IOutputDataStreamDecorator
{
public:
	EncodeStreamDecorator(OutputStreamPtr&& stream, int seed)
		: IOutputDataStreamDecorator(move(stream))
	{
		CodeDecodeGenerator gen;
		gen.Generate(seed);
		m_encodeMap = gen.GetEncodeMap();
	}

	void WriteByte(uint8_t data) override
	{
		IOutputDataStreamDecorator::WriteByte(m_encodeMap[data]);
	}

	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		auto data = static_cast<const uint8_t*>(srcData);
		for (std::streamsize i = 0; i < size; ++i)
		{
			WriteByte(data[i]);
		}
	}

private:
	std::unordered_map<uint8_t, uint8_t> m_encodeMap;
};