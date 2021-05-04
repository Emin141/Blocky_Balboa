#pragma once

#include <iostream>
#include <vector>

class Mesh
{
public:
	//Prevents me from doing something stupid like not loading the mesh
	Mesh() = delete;
	Mesh(const Mesh& otherMesh) = delete;

	//The constructor loads vertex positions and vertex indices
	Mesh(const std::string& mesh_path);

	inline auto getVertexPositions() const { return VertexPositions; }
	inline auto getVertexIndices() const { return VertexIndices; }

private:
	std::vector<float> VertexPositions;
	std::vector<uint32_t> VertexIndices;
};