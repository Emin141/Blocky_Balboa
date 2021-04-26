#version 400

uniform mat4 mvp;

layout(location=0) in vec3 vertex_position;
layout(location=1) in vec2 a_tex_coords;

out vec2 tex_coords;

void main() {
    tex_coords = a_tex_coords;
    gl_Position = mvp * vec4(vertex_position, 1.0f);
}