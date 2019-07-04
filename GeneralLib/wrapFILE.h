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
* 
* @param filePath A FilePath to the FILE we're going to use
* @param mode What mode should we open the file in
* @return A proper std::unique_ptr to the file stream
*/
std::unique_ptr<FILE, FILEDeleter> make_fopen(FilePath filePath, std::string mode);