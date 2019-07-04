#include "wrapFILE.h"

#include "FilePath.h"


void FILEDeleter::operator()(FILE *pFile)
{
	if (pFile)
	{
		fclose(pFile);
	}
}


std::unique_ptr<FILE, FILEDeleter> make_fopen(FilePath filePath, std::string mode)
{
	FILE * fileHandle = nullptr;
	auto err = fopen_s(&fileHandle, filePath.toString().c_str(), mode.c_str());
	if (err != 0)
	{
		return nullptr;
	}

	return std::unique_ptr<FILE, FILEDeleter>(fileHandle);
}