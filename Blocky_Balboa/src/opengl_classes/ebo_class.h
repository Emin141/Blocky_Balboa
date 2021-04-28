#pragma once

#include <GL/glew.h>

class EBO
{
public:
	EBO() : m_ID(0) {}
	EBO(GLuint* indices, GLsizeiptr size);

	void Bind() const;
	void Unbind() const;
	void Delete() const;

private:
	GLuint m_ID;
};

