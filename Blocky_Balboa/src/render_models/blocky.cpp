#include "blocky.h"
#include "../math/cece_matrix4.h"
#include "../stb_image/stb_image.h"


Blocky::Blocky()
{
	//GLfloat vertex_data[] = {
	//		//positions				 //colors
	//	-1.0f, -1.0f,  1.0f,      1.0f, 0.0f, 0.0f,
	//	 1.0f, -1.0f,  1.0f,	  0.0f, 1.0f, 0.0f,
	//	 1.0f,  1.0f,  1.0f,	  0.0f, 0.0f, 1.0f,
	//	-1.0f,  1.0f,  1.0f,	  1.0f, 1.0f, 0.0f,
	//	-1.0f,  1.0f, -1.0f,	  1.0f, 0.0f, 1.0f,
	//	-1.0f, -1.0f, -1.0f,	  0.0f, 1.0f, 1.0f,
	//	 1.0f,  1.0f, -1.0f,	  1.0f, 1.0f, 1.0f,
	//	 1.0f, -1.0f, -1.0f,	  0.0f, 0.0f, 0.0f
	//};

	GLfloat vertex_data[] = {
		//positions				  //colors               //tex_coords
		-1.0f, -1.0f,  1.0f,      1.0f, 0.0f, 0.0f,      0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f,	  0.0f, 1.0f, 0.0f,		 1.0f, 1.0f,
		 1.0f,  1.0f,  1.0f,	  0.0f, 0.0f, 1.0f,		 0.0f, 0.0f,
		-1.0f,  1.0f,  1.0f,	  1.0f, 1.0f, 0.0f,		 1.0f, 0.0f,
		-1.0f,  1.0f, -1.0f,	  1.0f, 0.0f, 1.0f,		 0.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,	  0.0f, 1.0f, 1.0f,		 1.0f, 1.0f,
		 1.0f,  1.0f, -1.0f,	  1.0f, 1.0f, 1.0f,		 0.0f, 0.0f,
		 1.0f, -1.0f, -1.0f,	  0.0f, 0.0f, 0.0f,		 1.0f, 0.0f,
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
		1, 5, 7,
	};

	glGenBuffers(1, &m_vertex_buffer_ID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_ID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);

	glGenTextures(1, &m_texture_ID);
	glActiveTexture(GL_TEXTURE1);
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

	glGenVertexArrays(1, &m_vao_ID);
	glBindVertexArray(m_vao_ID);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), NULL);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));

	glGenBuffers(1, &m_index_buffer_ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer_ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

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

void Blocky::draw() const
{
	bind();
	glDrawElements(GL_TRIANGLES, 12 * 3, GL_UNSIGNED_INT, 0);
	unbind();	
}

void Blocky::setWorldPosition(const cece::Vector3& world_position) const
{
	cece::Matrix4 model_matrix = cece::createTranslationMatrix(world_position);
	m_Program->setUniform("model_matrix", model_matrix.c_arr());
}

void Blocky::bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_texture_ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer_ID);
	glBindVertexArray(m_vao_ID);
	m_Program->useProgram();
}

void Blocky::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, -1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, -1);
	glBindVertexArray(-1);
	glUseProgram(-1);
}