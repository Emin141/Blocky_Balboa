#include <cstdio>

#include "vao_class.h"

VAO::VAO()
{
	glGenVertexArrays(1, &m_ID);
}

void VAO::LinkAttrib(const VBO& vbo, GLuint layout, GLuint num_components, GLenum type, GLsizeiptr stride, void* offset) const
{
	vbo.Bind();

	glVertexAttribPointer(layout, num_components, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);

	vbo.Unbind();
}

void VAO::Bind() const
{
	glBindVertexArray(m_ID);
}

void VAO::Unbind() const
{
	glBindVertexArray(0);
}

void VAO::Delete() const
{
	glDeleteVertexArrays(1, &m_ID);
}