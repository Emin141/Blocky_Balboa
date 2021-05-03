#pragma once

#include "mesh_class.h"
#include "../cece_math/cece_vector3.h"
#include "../opengl_classes/shader_class.h"
#include "../opengl_classes/vbo_class.h"
#include "../opengl_classes/vao_class.h"
#include "../opengl_classes/ebo_class.h"
#include "../opengl_classes/texture_class.h"
#include "../cece_math/cece_matrix4.h"

extern cece::Matrix4 g_MVP;

class Entity
{
public:
	Entity() = delete;
	Entity(
		const std::string& mesh_path, 
		const std::string& v_shader_path,
		const std::string& f_shader_path
	);
	~Entity();

	void draw();
	void setWorldPosition(const cece::Vector3& world_position) const;
	void updateWorldPosition(const cece::Vector3& world_position) const;
	inline Shader* accessProgram() const { return m_Program; }

private:
	Mesh* m_Mesh;
	Shader* m_Program;

	VBO m_vbo;
	VAO m_vao;
	EBO m_ebo;
	Texture m_texture;

	GLuint m_number_of_faces;

private:
	void setMVP() const;
	void updateMVP() const;
};