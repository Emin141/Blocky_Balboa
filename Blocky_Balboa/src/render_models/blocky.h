#pragma once

#include <GL/glew.h>
#include "../opengl_classes/shader_class.h"
#include "../cece_math/cece_vector3.h"

class Blocky
{
public:
	Blocky();
	~Blocky();
	void setWorldPosition(const cece::Vector3& world_position) const;
 	inline Shader* accessProgram() const { return m_Program; };
	void draw() const;

protected:
	Shader* m_Program;

private:
	GLuint m_vertex_buffer_ID;
	GLuint m_index_buffer_ID;
	GLuint m_texture_ID;
	GLuint m_vao_ID;

	void bind() const;
	void unbind() const;
};

