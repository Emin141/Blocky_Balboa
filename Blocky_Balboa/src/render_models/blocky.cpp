#include "blocky.h"
#include "../math/cece_matrix4.h"

Blocky::Blocky()
{
	GLfloat vertex_data[] = {
			//positions				 //colors
		-1.0f, -1.0f,  1.0f,      1.0f, 0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f,	  0.0f, 1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f,	  0.0f, 0.0f, 1.0f,
		-1.0f,  1.0f,  1.0f,	  1.0f, 1.0f, 0.0f,
		-1.0f,  1.0f, -1.0f,	  1.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,	  0.0f, 1.0f, 1.0f,
		 1.0f,  1.0f, -1.0f,	  1.0f, 1.0f, 1.0f,
		 1.0f, -1.0f, -1.0f,	  0.0f, 0.0f, 0.0f
	};

	GLuint indices[] = {
		0, 1, 2,
		0, 2, 3,
		0, 3, 4,
		0, 4, 5,
		5, 4, 6,
		5, 6, 7,
		7, 6, 2,
		7, 2, 1,
		2, 6, 4,
		2, 4, 3,
		1, 0, 5,
		1, 5, 7
	};

	glGenBuffers(1, &m_vertex_buffer_ID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_ID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), NULL);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	glGenBuffers(1, &m_index_buffer_ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer_ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	Shader vs(Shader::Type::VERTEX, "./res/shaders/blocky_balboa.vert");
	Shader fs(Shader::Type::FRAGMENT, "./res/shaders/blocky_balboa.frag");

	m_Program = new ShaderProgram(vs, fs);

	m_Program->useProgram();
	m_Program->setUniform("model_matrix", cece::createIdentityMatrix().c_arr());
}

Blocky::~Blocky()
{
	delete m_Program;
}

void Blocky::draw()
{
	m_Program->useProgram();

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer_ID);

	glDrawElements(GL_TRIANGLES, 12 * 3, GL_UNSIGNED_INT, NULL);

	glUseProgram(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Blocky::setWorldPosition(const cece::Vector3& world_position) const
{
	cece::Matrix4 model_matrix = cece::createTranslationMatrix(world_position);
	m_Program->setUniform("model_matrix", model_matrix.c_arr());
}

void Blocky::updateWorldPosition(const cece::Vector3& world_position) const
{
	cece::Matrix4 model_matrix = cece::createTranslationMatrix(world_position);
	m_Program->updateUniform("model_matrix", model_matrix.c_arr());
}