#pragma once

#include <GL/glew.h>
#include "vbo_class.h"

class VAO
{
public:
	VAO();

	void LinkAttrib(const VBO& vbo, GLuint layout, GLuint num_components, GLenum type, GLsizeiptr stride, void* offset) const;
	void Bind() const;
	void Unbind() const;
	void Delete() const;
private:
	GLuint m_ID;
};

