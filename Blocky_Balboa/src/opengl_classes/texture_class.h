#pragma once

#include <GL/glew.h>
#include "../stb/stb_image.h"

#include "shader_class.h"

class Texture
{
public:
	GLenum type;
	Texture() : m_ID(0), type(GL_TEXTURE_2D) {}
	Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

	void texUnit(Shader& shader_program, const char* uniform, GLuint unit);
	void Bind();
	void Unbind();
	void Delete();

private:
	GLuint m_ID;
};