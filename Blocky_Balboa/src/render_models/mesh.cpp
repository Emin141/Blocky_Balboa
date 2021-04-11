#include "mesh.h"

#include <cstring>
#include <fstream>

Mesh::Mesh(const std::string& mesh_path)
{
	std::ifstream input_file;
	input_file.open(mesh_path);
	if (!input_file)
	{
		std::cerr << "Could not open mesh file at "
			<< mesh_path.c_str() << "!\n";

		std::cin.get();
		exit(-1);
	}

	std::string line;

	while (!input_file.eof())
	{
		input_file >> line;

		if (line == "v")
		{
			input_file >> line;
			VertexPositions.push_back(atof(line.c_str()));
			input_file >> line;
			VertexPositions.push_back(atof(line.c_str()));
			input_file >> line;
			VertexPositions.push_back(atof(line.c_str()));
		}

		if (line == "f")
		{
			input_file >> line;
			VertexIndices.push_back(atof(line.c_str()));
			input_file >> line;
			VertexIndices.push_back(atof(line.c_str()));
			input_file >> line;
			VertexIndices.push_back(atof(line.c_str()));
		}
	}
}