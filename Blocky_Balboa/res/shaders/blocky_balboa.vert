#version 330 core

uniform mat4 mvp;
uniform mat4 model_matrix;

layout(location=0) in vec3 vertex_position;
layout(location=1) in vec3 vertex_color;
layout(location=2) in vec2 a_tex_coords;

out vec3 color;
out vec2 tex_coords;

void main() {
    gl_Position = mvp * model_matrix * vec4(vertex_position, 1.0f);
    color = vertex_color;
    tex_coords = a_tex_coords;
}