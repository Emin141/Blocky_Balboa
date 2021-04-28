#include "terrain.h"
#include "../stb/stb_image.h"

Terrain::Terrain()
{
	GLfloat vertex_data[] = {
		//positions                    //texture coords
		-100.0f, -1.0f,  100.0f,        0.0f, 1.0f,
		-100.0f, -1.0f, -100.0f,		0.0f, 0.0f,
		 100.0f, -1.0f,  100.0f,		1.0f, 1.0f,
		 100.0f, -1.0f, -100.0f,		1.0f, 0.0f
	};

	glGenBuffers(1, &m_vertex_buffer_ID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_ID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);

	glGenTextures(1, &m_texture_ID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture_ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(1);
	unsigned char* data = stbi_load("./res/textures/heatmap.png", &width, &height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("Failed to load image! STBI reason: %s\n", stbi_failure_reason());
	}
	stbi_image_free(data);

	GLuint indices[] = {
		2, 1, 0,
		2, 3, 1
	};
	glGenBuffers(1, &m_index_buffer_ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer_ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &m_vao_ID);
	glBindVertexArray(m_vao_ID);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	m_Program = new Shader("./res/shaders/terrain.vert", "./res/shaders/terrain.frag");

	m_Program->Activate();
}

Terrain::~Terrain()
{
	delete m_Program;
	//glDeleteTextures(1, &m_texture_ID);
}

void Terrain::draw() const
{
	bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	unbind();
}

void Terrain::bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_texture_ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer_ID);
	glBindVertexArray(m_vao_ID);
	m_Program->Activate();
}

void Terrain::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, -1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, -1);
	glBindVertexArray(-1);
	glUseProgram(-1);
}