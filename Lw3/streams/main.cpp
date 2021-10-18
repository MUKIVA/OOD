#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <queue>
#include <array>
#include <cstdint>
#include <memory>
#include <random>
#include <algorithm>

using namespace std;

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

	unordered_map<uint8_t, uint8_t> GetDecodeMap() const
	{
		unordered_map<uint8_t, uint8_t> decodeMap;
		for (int i = 0; i <= 255; ++i)
		{
			decodeMap.insert(make_pair(m_encode[i], m_decode[i]));
		}
		return decodeMap;
	}

	unordered_map<uint8_t, uint8_t> GetEncodeMap() const
	{
		unordered_map<uint8_t, uint8_t> decodeMap;
		for (int i = 0; i <= 255; ++i)
		{
			decodeMap.insert(make_pair(m_decode[i], m_encode[i]));
		}
		return decodeMap;
	}

private:
	array<uint8_t, 256> m_decode;
	array<uint8_t, 256> m_encode;
};

class IOutputDataStream
{
public:
	// Записывает в поток данных байт
	// Выбрасывает исключение std::ios_base::failure в случае ошибки
	virtual void WriteByte(uint8_t data) = 0;

	// Записывает в поток блок данных размером size байт, 
	// располагающийся по адресу srcData,
	// В случае ошибки выбрасывает исключение std::ios_base::failure
	virtual void WriteBlock(const void * srcData, std::streamsize size) = 0;

	virtual ~IOutputDataStream() = default;
};

class IOutputDataStreamDecorator : public IOutputDataStream
{
public:
	IOutputDataStreamDecorator(IOutputDataStream& outStream)
		: m_outStream(&outStream)
	{
	}

	void WriteByte(uint8_t data) override
	{
		m_outStream->WriteByte(data);
	}

	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		m_outStream->WriteBlock(srcData, size);
	}

private:
	IOutputDataStream* m_outStream;
};

class EncodeStreamDecorator : public IOutputDataStreamDecorator
{
public:
	EncodeStreamDecorator(IOutputDataStream& stream, int seed)
		: IOutputDataStreamDecorator(stream)
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
	unordered_map<uint8_t, uint8_t> m_encodeMap;
};

class CompressStreamDecorator : public IOutputDataStreamDecorator
{
public:
	CompressStreamDecorator(IOutputDataStream&& stream)
		: IOutputDataStreamDecorator(stream)
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

class CFileOutputStream : public IOutputDataStream
{
public:
	CFileOutputStream(string const& filePath)
		: m_file(make_unique<ofstream>(ofstream(filePath, ios::binary)))
	{
	}

	void WriteByte(uint8_t data) override
	{
		if (m_file == nullptr)
		{
			throw ios_base::failure("file stream isn't open");
		}

		(*m_file).write((char*)(&data), sizeof(data));
	}

	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		if (m_file == nullptr)
		{
			throw ios_base::failure("file stream isn't open");
		}

		(*m_file).write((const char*)(srcData), size);
	}

	void Close()
	{
		(*m_file).close();
		m_file = nullptr;
	}

private:
	unique_ptr<ofstream> m_file = nullptr;
};

class CMemoryOutputStream : public IOutputDataStream
{
public:

	queue<uint8_t> GetMemory() const
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
			throw ios_base::failure("Failed to allocate memory");
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
			throw ios_base::failure("Failed to allocate memory");
		}
	}

private:
	queue<uint8_t> m_memory;
};

class IInputDataStream
{
public:
	// Возвращает признак достижения конца данных потока
	// Выбрасывает исключение std::ios_base::failuer в случае ошибки
	virtual bool IsEOF()const = 0;

	// Считывает байт из потока. 
	// Выбрасывает исключение std::ios_base::failure в случае ошибки
	virtual uint8_t ReadByte() = 0;

	// Считывает из потока блок данных размером size байт, записывая его в память
	// по адресу dstBuffer
	// Возвращает количество реально прочитанных байт. Выбрасывает исключение в случае ошибки
	virtual std::streamsize ReadBlock(void * dstBuffer, std::streamsize size) = 0;

	virtual ~IInputDataStream() = default;
};

class IInputDataStreamDecorator : public IInputDataStream
{
public:
	IInputDataStreamDecorator(IInputDataStream& inputStream)
		: m_inputStream(&inputStream)
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
	IInputDataStream* m_inputStream;
};

class DecodeStreamDecorator : public IInputDataStreamDecorator
{
public:
	DecodeStreamDecorator(IInputDataStream& stream, int seed)
		: IInputDataStreamDecorator(stream)
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
	}

private:
	unordered_map<uint8_t, uint8_t> m_decodeMap;
};

class DecompresStreamDecorator : public IInputDataStreamDecorator
{
public:
	DecompresStreamDecorator(IInputDataStream&& stream)
		: IInputDataStreamDecorator(stream)
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
		swap(tmp, m_realReadByte);
		return tmp;
	}

private:
	uint8_t m_count = 0;
	uint8_t m_currentByte = 0;
	std::streamsize m_realReadByte = 0;
};

class CFileInputStream : public IInputDataStream
{
public:
	CFileInputStream(string const& filePath)
		: m_file(make_unique<ifstream>(ifstream(filePath, ios::binary)))
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
	unique_ptr<ifstream> m_file = nullptr;
};

class CMemoryInputStream : public IInputDataStream
{
public:

	CMemoryInputStream(queue<uint8_t> const& memory)
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
	queue<uint8_t> m_memory;
};

int main()
{
	CFileOutputStream outF("out.dat");
	CompressStreamDecorator(EncodeStreamDecorator(outF, 1)).WriteBlock("Hello world!", 12);
	outF.Close();
	uint8_t* ptr = new uint8_t();
	CFileInputStream inF("out.dat");
	DecompresStreamDecorator(DecodeStreamDecorator(inF, 1)).ReadBlock(ptr, 12);
 	return 0;
}