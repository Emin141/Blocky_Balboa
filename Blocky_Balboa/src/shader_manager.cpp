#include <cstdio>
#include <map>

#include "shader_manager.h"
#include "shader_parser.h"
#include "logger.h"

Shader::Shader(Type shader_type, const std::string& source_path)
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

ShaderProgram::ShaderProgram(const Shader& vertex_shader, const Shader& fragment_shader)
{
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
}

void ShaderProgram::setUniform(const char* uniform_name, float r, float g, float b, float a)
{
	uniform_location[uniform_index] = glGetUniformLocation(m_ProgramID, uniform_name);
	uniform_map.insert(std::pair(uniform_name, uniform_location[uniform_index]));
	uniform_index++;
	useProgram();
	glUniform4f(uniform_map[uniform_name], r, g, b, a);
}

void ShaderProgram::setUniform(const char* uniform_name, float mat[16])
{
	uniform_location[uniform_index] = glGetUniformLocation(m_ProgramID, uniform_name);
	uniform_map.insert(std::pair(uniform_name, uniform_location[uniform_index]));
	uniform_index++;
	useProgram();
	glUniformMatrix4fv(uniform_map[uniform_name], 1, GL_FALSE, mat);
}

void ShaderProgram::updateUniform(const char* uniform_name, float mat[16])
{
	useProgram();
	glUniformMatrix4fv(uniform_map[uniform_name], 1, GL_FALSE, mat);
}

void ShaderProgram::updateUniform(const char* uniform_name, float r, float g, float b, float a)
{
	useProgram();
	glUniform4f(uniform_map[uniform_name], r, g, b, a);
}
