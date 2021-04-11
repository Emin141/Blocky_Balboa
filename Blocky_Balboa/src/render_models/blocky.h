#pragma once

#include <GL/glew.h>
#include "../shader_manager.h"
#include "../math/cece_vector3.h"

class Blocky
{
public:
	Blocky();
	~Blocky();
	void setWorldPosition(const cece::Vector3& world_position) const;
	//void updateWorldPosition(const cece::Vector3& world_position) const;
 	inline ShaderProgram* accessProgram() const { return m_Program; };
	void draw();

protected:
	ShaderProgram* m_Program;

private:
	GLuint m_vertex_buffer_ID;
	GLuint m_index_buffer_ID;
	GLuint m_vao;
};

