#pragma once
#include "IInputDataStream.h"
#include <fstream>

class CFileInputStream : public IInputDataStream
{
public:
	CFileInputStream(std::string const& filePath)
		: m_file(std::make_unique<std::ifstream>(std::ifstream(filePath, std::ios::binary)))
	{
	}

	bool IsEOF() const override
	{
		if (m_file == nullptr)
		{
			throw std::ios_base::failure("file stream isn't open");
		}

		return (*m_file).eof();
	}

	uint8_t ReadByte() override
	{
		if (m_file == nullptr)
		{
			throw std::ios_base::failure("file stream isn't open");
		}

		uint8_t byte;
		if (!((*m_file).read((char*)(&byte), sizeof(uint8_t))))
		{
			throw std::ios_base::failure("Failed to read from file");
		}

		return byte;
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
	{

		if (m_file == nullptr)
		{
			throw std::ios_base::failure("file stream isn't open");
		}

		if (!((*m_file).read(reinterpret_cast<char*>(dstBuffer), size)))
		{
			throw std::ios_base::failure("Failed to read from file");
		}

		return 0;
	}

private:
	std::unique_ptr<std::ifstream> m_file = nullptr;
};