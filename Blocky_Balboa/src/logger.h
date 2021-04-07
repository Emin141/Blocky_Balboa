#pragma once
#pragma warning(disable : 4996)

#define GL_LOG_FILE "gl.log"

bool restart_gl_log();
bool gl_log(const char* message, ...);
bool gl_log_err(const char* message, ...);
void _print_shader_info_log(GLuint shader_index);
void _print_program_info_log(GLuint program);
const char* GL_type_to_string(GLenum type);
void print_all(GLuint program);
bool is_valid(GLuint program);