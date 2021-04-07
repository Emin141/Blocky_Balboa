#pragma once

#include <GL/glew.h>
#include "../shader_manager.h"

class Blocky
{
public:
	Blocky();
	~Blocky();
	inline ShaderProgram* accessProgram() const { return m_Program; };
	void draw();

public:
	ShaderProgram* m_Program;

private:
	GLuint m_positions_buffer_ID;
	GLuint m_colors_buffer_ID;
	GLuint m_index_buffer_ID;
	GLuint m_vao;
};

