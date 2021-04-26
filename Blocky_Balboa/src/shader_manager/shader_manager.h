#pragma once
#include <GL/glew.h>
#include <iostream>
#include <map>

class Shader
{
public:
	enum class Type {
		VERTEX = 0,
		FRAGMENT = 1
	};
	Shader() = delete;
	Shader(const Shader& otherShader) = delete;
	Shader(Type shader_type, const std::string& source_path);
	inline GLuint getShaderID() const { return m_ShaderID; }
private:
	GLuint m_ShaderID;
};

class ShaderProgram
{
public:
	ShaderProgram() = delete;
	ShaderProgram(const ShaderProgram& otherProgram) = delete;
	ShaderProgram(const Shader& vertex_shader, const Shader& fragment_shader);
	inline GLuint getProgramID() const { return m_ProgramID; }
	inline void useProgram() { glUseProgram(m_ProgramID); }

	void setUniform(const char* uniform_name, float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);
	void setUniform(const char* uniform_name, float mat[16]);
	
	void updateUniform(const char* uniform_name, float mat[16]);
	void updateUniform(const char* uniform_name, float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);
private:
	GLuint m_ProgramID;
	GLuint uniform_index;
	GLuint uniform_location[32];
	std::map<const char*, GLuint> uniform_map;
};