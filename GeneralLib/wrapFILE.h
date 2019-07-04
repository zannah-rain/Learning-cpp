#pragma once
#include <fstream>
#include <memory>
#include <string>

// Forward declarations
class FilePath;

/**
* Stateless destructor 
*/
struct FILEDeleter
{
	void operator()(FILE *pFile);
};

/**
* Create a std::unique_ptr for a FILE object
*/
std::unique_ptr<FILE, FILEDeleter> make_fopen(FilePath filePath, std::string mode);