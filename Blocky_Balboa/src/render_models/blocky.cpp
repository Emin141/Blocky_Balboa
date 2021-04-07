#include "blocky.h"

Blocky::Blocky()
{
	GLfloat vertex_positions[] = {
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f
	};

	GLfloat vertex_colors[] = {
		0.5f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f,
		0.0f, 0.0f, 0.5f,
		0.5f, 0.5f, 0.0f,
		0.5f, 0.0f, 0.5f,
		0.0f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		0.0f, 0.0f, 0.0f
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

	glGenBuffers(1, &m_positions_buffer_ID);
	glBindBuffer(GL_ARRAY_BUFFER, m_positions_buffer_ID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_positions), vertex_positions, GL_STATIC_DRAW);

	glGenBuffers(1, &m_colors_buffer_ID);
	glBindBuffer(GL_ARRAY_BUFFER, m_colors_buffer_ID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_colors), vertex_colors, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_positions_buffer_ID);
	glGenBuffers(1, &m_index_buffer_ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer_ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	Shader vs(Shader::Type::VERTEX, "./res/shaders/test.vert");
	Shader fs(Shader::Type::FRAGMENT, "./res/shaders/test.frag");

	m_Program = new ShaderProgram(vs, fs);

	m_Program->useProgram();
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