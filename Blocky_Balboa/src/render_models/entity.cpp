#include <iostream>

#include "entity.h"

#include "../cece_math/cece_matrix4.h"

Entity::Entity(const std::string& mesh_path, const std::string& v_shader_path,
	const std::string& f_shader_path)
{
	//creating shader from source
	m_Program = new Shader(v_shader_path, f_shader_path);
	m_Program->Activate();
	m_Program->setUniform("model_matrix", cece::createIdentityMatrix().c_arr());
	setMVP();

	//creating VAO
	m_vao.Bind();

#define MESH_LOADING_WORKS
#ifdef MESH_LOADING_WORKS
	//loading vbo and ebo data from mesh file
	m_Mesh = new Mesh(mesh_path);

	//Binding vertex buffer
	size_t vertex_positions_size = m_Mesh->getVertexPositions().size();
	GLfloat* vertex_positions = new float[vertex_positions_size];
	for (int i = 0; i < vertex_positions_size; i++)
	{
		vertex_positions[i] = m_Mesh->getVertexPositions()[i];
	}
	m_vbo = VBO(vertex_positions, vertex_positions_size * sizeof(float));
	//std::cout << vertex_positions_size << " " << sizeof(float) * vertex_positions_size;

	//Binding index buffer
	size_t vertex_indices_size = m_Mesh->getVertexIndices().size();
	GLuint* vertex_indices = new GLuint[vertex_indices_size];
	for (int i = 0; i < vertex_indices_size; i++)
	{
		vertex_indices[i] = m_Mesh->getVertexIndices()[i] - 1;
		//the -1 is because .obj files count from 1, not 0
	}
	m_ebo = EBO(vertex_indices, vertex_indices_size * sizeof(unsigned int));

	m_vbo.Bind();
	m_ebo.Bind();

	//setting the attribute
	m_vao.LinkAttrib(m_vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

	//acquiring number of faces
	m_number_of_faces = vertex_indices_size;

	//clearing data, no longer used
	delete[] vertex_positions;
	delete[] vertex_indices;
	delete m_Mesh;

#else

	GLfloat vertices[] =
	{ //     COORDINATES   
		-0.5f, 0.0f,  0.5f,
		-0.5f, 0.0f, -0.5f,
		 0.5f, 0.0f, -0.5f,
		 0.5f, 0.0f,  0.5f,
		 0.0f, 0.8f,  0.0f
	};

	// Indices for vertices order
	GLuint indices[] =
	{
		0, 1, 2,
		0, 2, 3,
		0, 1, 4,
		1, 2, 4,
		2, 3, 4,
		3, 0, 4
	};

	m_vbo = VBO(vertices, sizeof(vertices));
	m_ebo = EBO(indices, sizeof(indices));

	m_vbo.Bind();
	m_ebo.Bind();

	m_vao.LinkAttrib(m_vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	m_number_of_faces = 3 * sizeof(indices);
#endif
	//unbinding everything
	m_vao.Unbind();
	m_vbo.Unbind();
	m_ebo.Unbind();
}

Entity::~Entity()
{
	delete m_Program;
}

void Entity::setWorldPosition(const cece::Vector3& world_position) const
{
	m_Program->setUniform(
		"model_matrix",
		(cece::createScalingMatrix(3.0f) * cece::createTranslationMatrix(world_position)).c_arr()
	);
}

void Entity::draw()
{
	m_Program->Activate();
	updateMVP();

	m_ebo.Bind();
	m_vao.Bind();

	glDrawElements(GL_TRIANGLES, m_number_of_faces, GL_UNSIGNED_INT, NULL);

	glUseProgram(0);
	m_vao.Unbind();
	m_ebo.Unbind();
}

void Entity::setMVP() const
{
	m_Program->setUniform("mvp", g_MVP.c_arr());
}

void Entity::updateMVP() const
{
	m_Program->updateUniform("mvp", g_MVP.c_arr());
}