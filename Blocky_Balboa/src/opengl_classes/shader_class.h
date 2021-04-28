#pragma once
#include <GL/glew.h>
#include <iostream>
#include <map>


class Shader
{
public:
	Shader() = delete;
	Shader(const Shader& otherProgram) = delete;
	Shader(const std::string& vertex_shader_source_path, const std::string& fragment_shader_source_path);
	inline ~Shader() { glDeleteProgram(m_ProgramID); }
	inline GLuint getProgramID() const { return m_ProgramID; }
	inline void Activate() { glUseProgram(m_ProgramID); }

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