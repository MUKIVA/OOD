#pragma once
#include <unordered_map>
#include <algorithm>
#include <random>
#include <cstdint>
#include <array>

class CodeDecodeGenerator
{
public:
	CodeDecodeGenerator()
	{
		for (int i = 0; i <= 255; ++i)
		{
			m_decode[i] = i;
			m_encode[i] = i;
		}
		Generate();
	}

	void Generate(int seed = 0)
	{
		std::shuffle(m_encode.begin(), m_encode.end(), std::default_random_engine(seed));
	}

	std::unordered_map<uint8_t, uint8_t> GetDecodeMap() const
	{
		std::unordered_map<uint8_t, uint8_t> decodeMap;
		for (int i = 0; i <= 255; ++i)
		{
			decodeMap.insert(std::make_pair(m_encode[i], m_decode[i]));
		}
		return decodeMap;
	}

	std::unordered_map<uint8_t, uint8_t> GetEncodeMap() const
	{
		std::unordered_map<uint8_t, uint8_t> decodeMap;
		for (int i = 0; i <= 255; ++i)
		{
			decodeMap.insert(std::make_pair(m_decode[i], m_encode[i]));
		}
		return decodeMap;
	}

private:
	std::array<uint8_t, 256> m_decode;
	std::array<uint8_t, 256> m_encode;
};