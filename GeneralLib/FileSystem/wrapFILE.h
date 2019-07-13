#pragma once
#include <fstream>
#include <memory>
#include <string>

// Forward declarations
class C_FilePath;


/**
* Stateless destructor 
*/
struct S_FILEDeleter
{
	void operator()(FILE *pFile);
};

/**
* Create a std::unique_ptr for a FILE object
* 
* @param filePath A C_FilePath to the FILE we're going to use
* @param mode What mode should we open the file in
* @return A proper std::unique_ptr to the file stream
*/
std::unique_ptr<FILE, S_FILEDeleter> make_fopen(C_FilePath filePath, std::string mode);