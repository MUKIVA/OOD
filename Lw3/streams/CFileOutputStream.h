#pragma once
#include "IOutputDataStream.h"
#include <iostream>
#include <fstream>
#include <memory>

class CFileOutputStream : public IOutputDataStream
{
public:
	CFileOutputStream(std::string const& filePath)
		: m_file(std::make_unique<std::ofstream>(std::ofstream(filePath, std::ios::binary)))
	{
	}

	void WriteByte(uint8_t data) override
	{
		if (m_file == nullptr)
		{
			throw std::ios_base::failure("file stream isn't open");
		}

		(*m_file).write((char*)(&data), sizeof(data));
	}

	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		if (m_file == nullptr)
		{
			throw std::ios_base::failure("file stream isn't open");
		}

		(*m_file).write((const char*)(srcData), size);
	}

	void Close()
	{
		(*m_file).close();
		m_file = nullptr;
	}

private:
	std::unique_ptr<std::ofstream> m_file = nullptr;
};