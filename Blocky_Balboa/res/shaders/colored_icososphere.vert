#version 330 core

layout(location=0) in vec3 a_position;
layout(location=1) in vec2 a_tex_coords;

uniform mat4 model_matrix;
uniform mat4 mvp;

void main() {
    vec2 temporary = a_tex_coords;
    gl_Position = vec4(a_position, 1.0f);
}