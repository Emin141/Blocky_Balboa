#pragma once

#include <GL/glew.h>
#include "../opengl_classes/shader_class.h"

class Terrain
{
public:
	Terrain();
	~Terrain();
	inline Shader* accessProgram() const { return m_Program; };
	void draw() const;

private:
	Shader* m_Program;
	GLuint m_vertex_buffer_ID, m_index_buffer_ID;
	GLuint m_texture_ID;
	GLuint m_vao_ID;

	void bind() const;
	void unbind() const;
};