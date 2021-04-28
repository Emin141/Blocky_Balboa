#include "shader_parser.h"

#include <cstring>
#include <fstream>
#include <sstream>

std::string getShaderSource(const std::string& filepath)
{
	std::ifstream input_file;
	input_file.open(filepath);
	if (!input_file)
	{
		fprintf(stderr, "Could not open file at %s!\n", filepath.c_str());
	}

	std::string line;
	std::stringstream ss;

	while (getline(input_file, line))
	{
		ss << line << '\n';
	}

	return ss.str();
}
