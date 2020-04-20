#pragma once

#include <fstream>
#include <string>
#include <map>
#include <iostream>

class FileIO
{
public:
	FileIO() = default;
	~FileIO() = default;

	std::map<std::string, std::string> read_file(std::string filepath,
		std::string delimeter);

private:

};

