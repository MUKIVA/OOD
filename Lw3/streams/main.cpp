#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <memory>
#include "CFileInputStream.h"
#include "CFileOutputStream.h"
#include "IInputDataStream.h"
#include "IOutputDataStream.h"
#include "CompressStreamDecorator.h"
#include "DecompresStreamDecorator.h"
#include "EncodeStreamDecorator.h"
#include "DecodeStreamDecorator.h"

using namespace std;

const string COMPRESS_KEY = "--compress";
const string DECOMPRESS_KEY = "--decompress";
const string ENCRYPT_KEY = "--encrypt";
const string DECRYPT_KEY = "--decrypt";

struct IOStreams
{
	unique_ptr<IInputDataStream> ifs;
	unique_ptr<IOutputDataStream> ofs;
};

void PrintHelp()
{
	cout << "Invalid arguments" << endl
		 << "Usage: transform.exe [ options ] <intputFileName> <outputFileName>" << endl
		 << "--encrypt <key> encrypt file" << endl
		 << "--decrypt <key> decrypt file" << endl
		 << "--compress compress file" << endl
		 << "--decompress decompress file" << endl;
}

optional<IOStreams> ParseArgs(int argc, char* argv[])
{
	if (argc < 3)
	{
		return nullopt;
	}
	unique_ptr<IInputDataStream> inputStream = make_unique<CFileInputStream>(argv[argc - 2]);
	unique_ptr<IOutputDataStream> outputStream = make_unique<CFileOutputStream>(argv[argc - 1]);
	int i = 1;
	while (i < argc - 2)
	{
		string param = argv[i++];
		if (param == COMPRESS_KEY)
		{
			outputStream = make_unique<CompressStreamDecorator>(move(outputStream));
		}
		else if (param == DECOMPRESS_KEY)
		{
			inputStream = make_unique<DecompresStreamDecorator>(move(inputStream));
		}
		else if (param == ENCRYPT_KEY)
		{
			outputStream = make_unique<EncodeStreamDecorator>(move(outputStream), atoi(argv[i++]));
		}
		else if (param == DECRYPT_KEY)
		{
			inputStream = make_unique<DecodeStreamDecorator>(move(inputStream), atoi(argv[i++]));
		}
		else
		{
			return nullopt;
		}
	}
	IOStreams streams;
	streams.ifs = move(inputStream);
	streams.ofs = move(outputStream);
	return streams;
}

int main(int argc, char* argv[])
{
	auto streams = ParseArgs(argc, argv);
	if (!streams)
	{
		PrintHelp();
		return 1;
	}

	while (!streams->ifs->IsEOF())
	{
		try
		{
			streams->ofs->WriteByte(streams->ifs->ReadByte());
		}
		catch (...)
		{
			return 0;
		}
	}
 	return 0;
}