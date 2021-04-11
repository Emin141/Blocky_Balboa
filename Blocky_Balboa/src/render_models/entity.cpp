#include "entity.h"

#include "../math/cece_matrix4.h"

Entity::Entity(const std::string& mesh_path, const std::string& v_shader_path,
	const std::string& f_shader_path)
{
	m_Mesh = new Mesh(mesh_path);

	//Binding vertex (positions) buffer
	size_t vertex_positions_size = m_Mesh->getVertexPositions().size();
	float* vertex_positions = new float[vertex_positions_size];
	for (int i = 0; i < vertex_positions_size; i++)
	{
		vertex_positions[i] = m_Mesh->getVertexPositions()[i];
	}
	glGenBuffers(1, &m_vertex_buffer_ID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_ID);
	glBufferData(GL_ARRAY_BUFFER, vertex_positions_size * sizeof(float),
		(void*)vertex_positions, GL_STATIC_DRAW);
	delete[] vertex_positions;

	//Binding VAO
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, NULL, NULL);

	//Binding index buffer
	size_t vertex_indices_size = m_Mesh->getVertexIndices().size();
	GLuint* vertex_indices = new GLuint[vertex_indices_size];
	for (int i = 0; i < vertex_indices_size; i++)
	{
		vertex_indices[i] = m_Mesh->getVertexIndices()[i] - 1;
		//the -1 is because .obj files count from 1, not 0
	}
	glGenBuffers(1, &m_index_buffer_ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer_ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertex_indices_size * sizeof(GLuint),
		(void*)vertex_indices, GL_STATIC_DRAW);
	delete[] vertex_indices;

	//acquiring number of faces
	//coincides to be the number of elements in the index buffer
	m_number_of_faces = vertex_indices_size;

	//clearing mesh data, no longer used
	delete m_Mesh;

	glEnableVertexAttribArray(0);

	Shader vs(Shader::Type::VERTEX, v_shader_path);
	Shader fs(Shader::Type::FRAGMENT, f_shader_path);

	m_Program = new ShaderProgram(vs, fs);
	m_Program->useProgram();
	m_Program->setUniform("model_matrix", cece::createIdentityMatrix().c_arr());
}

Entity::~Entity()
{
	delete m_Program;
}

void Entity::setWorldPosition(const cece::Vector3& world_position) const
{
	m_Program->setUniform("model_matrix",
		(cece::createScalingMatrix(3.0f) *
			cece::createTranslationMatrix(world_position)).c_arr());
}

void Entity::draw()
{
	m_Program->useProgram();

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer_ID);

	//the points are for debug purposes
	glPointSize(5);
	glDrawElements(GL_POINTS, m_number_of_faces, GL_UNSIGNED_INT, NULL);
	
	glDrawElements(GL_TRIANGLES, m_number_of_faces, GL_UNSIGNED_INT, NULL);

	glUseProgram(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}