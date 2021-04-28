#include <cstdio>
#include <map>

#include "shader_class.h"
#include "shader_parser.h"
#include "../logger/logger.h"

class SubShader
{
public:
	enum class Type {
		VERTEX = 0,
		FRAGMENT = 1
	};
	SubShader() = delete;
	SubShader(const SubShader& otherShader) = delete;
	SubShader(Type shader_type, const std::string& source_path);
	inline GLuint getShaderID() const { return m_ShaderID; }
private:
	GLuint m_ShaderID;
};

SubShader::SubShader(Type shader_type, const std::string& source_path)
{
	std::string s_shader_source = getShaderSource(source_path);
	const char* c_shader_source = s_shader_source.c_str();

	switch (shader_type)
	{
	case Type::VERTEX:
		m_ShaderID = glCreateShader(GL_VERTEX_SHADER);
		break;
	case Type::FRAGMENT:
		m_ShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	default:
		m_ShaderID = 0;
		break;
	}

	glShaderSource(m_ShaderID, 1, &c_shader_source, NULL);
	glCompileShader(m_ShaderID);
	// check for compile errors
	int params = -1;
	glGetShaderiv(m_ShaderID, GL_COMPILE_STATUS, &params);
	if (GL_TRUE != params) {
		fprintf(stderr, "ERROR: GL shader index %i did not compile\n", m_ShaderID);
		_print_shader_info_log(m_ShaderID);
		exit(-1);
	}
	_print_shader_info_log(m_ShaderID);
}

Shader::Shader(const std::string& vertex_shader_source_path, const std::string& fragment_shader_source_path)
{
	SubShader vertex_shader(SubShader::Type::VERTEX, vertex_shader_source_path);
	SubShader fragment_shader(SubShader::Type::FRAGMENT, fragment_shader_source_path);
	m_ProgramID = glCreateProgram();
	glAttachShader(m_ProgramID, vertex_shader.getShaderID());
	glAttachShader(m_ProgramID, fragment_shader.getShaderID());
	glLinkProgram(m_ProgramID);
	// check if link was successful
	int params = -1;
	glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &params);
	if (GL_TRUE != params) {
		fprintf(stderr, "ERROR: could not link shader program GL index %u\n",
			m_ProgramID);
		_print_program_info_log(m_ProgramID);
		exit(-1);
	}

	print_all(m_ProgramID);
	uniform_index = 0;
	glDeleteShader(vertex_shader.getShaderID());
	glDeleteShader(fragment_shader.getShaderID());
}

void Shader::setUniform(const char* uniform_name, float r, float g, float b, float a)
{
	uniform_location[uniform_index] = glGetUniformLocation(m_ProgramID, uniform_name);
	uniform_map.insert(std::pair(uniform_name, uniform_location[uniform_index]));
	uniform_index++;
	Activate();
	glUniform4f(uniform_map[uniform_name], r, g, b, a);
}

void Shader::setUniform(const char* uniform_name, float mat[16])
{
	uniform_location[uniform_index] = glGetUniformLocation(m_ProgramID, uniform_name);
	uniform_map.insert(std::pair(uniform_name, uniform_location[uniform_index]));
	uniform_index++;
	Activate();
	glUniformMatrix4fv(uniform_map[uniform_name], 1, GL_FALSE, mat);
}

void Shader::updateUniform(const char* uniform_name, float mat[16])
{
	Activate();
	glUniformMatrix4fv(uniform_map[uniform_name], 1, GL_FALSE, mat);
}

void Shader::updateUniform(const char* uniform_name, float r, float g, float b, float a)
{
	Activate();
	glUniform4f(uniform_map[uniform_name], r, g, b, a);
}
