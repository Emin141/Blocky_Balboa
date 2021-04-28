#pragma once

#include "GL/glew.h"

class VBO
{
public:
	VBO() : m_ID(0) {}
	VBO(GLfloat* vertices, GLsizeiptr size);

	void Bind() const;
	void Unbind() const;
	void Delete() const;

private:
	GLuint m_ID;
};