#pragma once

#include <GL/glew.h>
#include "../shader_manager/shader_manager.h"

class Terrain
{
public:
	Terrain();
	~Terrain();
	inline ShaderProgram* accessProgram() const { return m_Program; };
	void draw() const;

private:
	ShaderProgram* m_Program;
	GLuint m_vertex_buffer_ID, m_index_buffer_ID;
	GLuint m_texture_ID;
	GLuint m_vao_ID;

	void bind() const;
	void unbind() const;
};