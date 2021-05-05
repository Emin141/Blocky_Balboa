#include <cstdio>
#include <map>

#include "shader_class.h"
#include "shader_parser.h"
#include "../logger/logger.h"

class SubShader
{
public:
	enum class Type
	{
		VERTEX = 0,
		FRAGMENT = 1
	};
	SubShader() = delete;
	SubShader(const SubShader &otherShader) = delete;
	SubShader(Type shader_type, const std::string &source_path);
	inline GLuint getShaderID() const { return m_ShaderID; }

private:
	GLuint m_ShaderID;
};

SubShader::SubShader(Type shader_type, const std::string &source_path)
{
	std::string s_shader_source = getShaderSource(source_path);
	const char *c_shader_source = s_shader_source.c_str();

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
	if (GL_TRUE != params)
	{
		fprintf(stderr, "ERROR: GL shader index %i did not compile\n", m_ShaderID);
		_print_shader_info_log(m_ShaderID);
		exit(-1);
	}
	_print_shader_info_log(m_ShaderID);
}

Shader::Shader(const std::string &vertex_shader_source_path, const std::string &fragment_shader_source_path)
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
	if (GL_TRUE != params)
	{
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

void Shader::set_uniform(UniformType _uniform_type, const char *_uniform_name, const void *_data)
{
	uniform_location[uniform_index] = glGetUniformLocation(m_ProgramID, _uniform_name);
	uniform_map.insert(std::pair(_uniform_name, uniform_location[uniform_index]));
	uniform_index++;
	Activate();
	switch (_uniform_type)
	{
	case UniformType::INT1:
		glUniform1i(uniform_map[_uniform_name], (GLint)(_data));
	case UniformType::VEC3:
		glUniform3fv(uniform_map[_uniform_name], 1, (const GLfloat *)(_data));
	case UniformType::MAT4:
		glUniformMatrix4fv(uniform_map[_uniform_name], 1, GL_FALSE, (const GLfloat *)(_data));
	default:
		break;
	}
}

void Shader::update_uniform(UniformType _uniform_type, const char *_uniform_name, const void *_data)
{
	Activate();
	switch (_uniform_type)
	{
	case UniformType::INT1:
		glUniform1i(uniform_map[_uniform_name], (GLint)(_data));
	case UniformType::VEC3:
		glUniform3fv(uniform_map[_uniform_name], 1, (const GLfloat *)(_data));
	case UniformType::MAT4:
		glUniformMatrix4fv(uniform_map[_uniform_name], 1, GL_FALSE, (const GLfloat *)(_data));
	default:
		break;
	}
}