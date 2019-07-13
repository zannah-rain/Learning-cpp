#include "wrapFILE.h"

#include "FilePath.h"


void S_FILEDeleter::operator()(FILE *pFile)
{
	if (pFile)
	{
		fclose(pFile);
	}
}


std::unique_ptr<FILE, S_FILEDeleter> make_fopen(C_FilePath filePath, std::string mode)
{
	FILE * fileHandle = nullptr;
	auto err = fopen_s(&fileHandle, filePath.toString().c_str(), mode.c_str());
	if (err != 0)
	{
		return nullptr;
	}

	return std::unique_ptr<FILE, S_FILEDeleter>(fileHandle);
}