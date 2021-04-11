#pragma once

#include "mesh.h"

class IRenderable
{
public:
	//virtual void loadMesh(const Mesh& mesh) = 0;
	virtual void draw() = 0;

};