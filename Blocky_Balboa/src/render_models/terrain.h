#pragma once

#include <GL/glew.h>
#include "../shader_manager/shader_manager.h"

class Terrain
{
public:
	Terrain();
	~Terrain();
	inline ShaderProgram* accessProgram() const { return m_Program; };
	void draw();

private:
	ShaderProgram* m_Program;
	GLuint m_positions_buffer_ID;
	GLuint m_vao;
};