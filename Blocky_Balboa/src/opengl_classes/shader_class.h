#pragma once
#include <GL/glew.h>
#include <iostream>
#include <map>

#include "../cece_math/cece_vector3.h"
#include "../cece_math/cece_matrix4.h"

enum class UniformType
{
	UNSPECIFIED = -1,
	INT1 = 0,
	VEC3 = 1,
	MAT4 = 2,

	TOTAL
};

class Shader
{
public:
	Shader() = delete;
	Shader(const Shader& otherProgram) = delete;
	Shader(const std::string& vertex_shader_source_path, const std::string& fragment_shader_source_path);
	inline ~Shader() { glDeleteProgram(m_ProgramID); }
	inline GLuint getProgramID() const { return m_ProgramID; }
	inline void Activate() { glUseProgram(m_ProgramID); }
	inline void Deactivate() { glUseProgram(0);}
	inline void Delete() { glDeleteProgram(m_ProgramID);}

	void set_uniform(UniformType _uniform_type, const char* _uniform_name, const void* _data);
	void update_uniform(UniformType _uniform_type, const char* _uniform_name, const void* _data);
	
private:
	GLuint m_ProgramID;
	GLuint uniform_index;
	GLuint uniform_location[32];
	std::map<const char*, GLuint> uniform_map;
};