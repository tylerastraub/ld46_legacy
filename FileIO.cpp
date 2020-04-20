#include "FileIO.h"

// Reads a .txt file and store its contents into a map.
// The standard delimiter is ':', though really any delimiter would
// work as long as it's specified correctly. Most importantly is that
// every file should have a FILE_TYPE key so that the game knows which
// keys should exist and it can properly access the map created.
//
// Different values for FILE_TYPE: LEVEL and DIALOG

std::map<std::string, std::string> FileIO::read_file(std::string filepath,
	std::string delimeter)
{
	std::ifstream file;
	std::string current_line;
	std::map<std::string, std::string> contents;

	file.open(filepath);
	if (file) {
		while (std::getline(file, current_line)) {
			std::string key = current_line.substr(0, current_line.find(delimeter));
			std::string value = current_line.substr(current_line.find(delimeter)
				+ delimeter.length());
			contents[key] = value;
		}
	}

	return contents;
}
