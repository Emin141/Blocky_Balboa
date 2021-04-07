#include "terrain.h"

Terrain::Terrain()
{
	GLfloat vertex_positions[] = {
		-1000.0f, -1.0f,  1000.0f,
		-1000.0f, -1.0f, -1000.0f,
		 1000.0f, -1.0f,  1000.0f,
		 1000.0f, -1.0f, -1000.0f
	};

	glGenBuffers(1, &m_positions_buffer_ID);
	glBindBuffer(GL_ARRAY_BUFFER, m_positions_buffer_ID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_positions), vertex_positions, GL_STATIC_DRAW);

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_positions_buffer_ID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	Shader vs(Shader::Type::VERTEX, "./res/shaders/terrain.vert");
	Shader fs(Shader::Type::FRAGMENT, "./res/shaders/terrain.frag");

	m_Program = new ShaderProgram(vs, fs);

	m_Program->useProgram();
}

Terrain::~Terrain()
{
	delete m_Program;
}

void Terrain::draw()
{
	glBindVertexArray(m_vao);
	m_Program->useProgram();

	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawArrays(GL_TRIANGLES, 1, 3);

	glUseProgram(0);
}