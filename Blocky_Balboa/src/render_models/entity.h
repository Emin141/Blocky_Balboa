#pragma once

#include "IRenderable.h"
#include "../math/cece_vector3.h"
#include "mesh.h"
#include "../shader_manager/shader_manager.h"
#include "../math/cece_matrix4.h"

class Entity : public IRenderable
{
public:
	Entity() = delete;
	Entity(const std::string& mesh_path, const std::string& v_shader_path,
		const std::string& f_shader_path);
	~Entity();

	void draw();
	void setMVP(const cece::Matrix4& mvp);
	void updateMVP(const cece::Matrix4& mvp);
	void setWorldPosition(const cece::Vector3& world_position) const;
	inline ShaderProgram* accessProgram() const { return m_Program; }

private:
	Mesh* m_Mesh;
	ShaderProgram* m_Program;
	GLuint m_vertex_buffer_ID;
	GLuint m_index_buffer_ID;
	GLuint m_number_of_faces;
	GLuint m_vao;
};