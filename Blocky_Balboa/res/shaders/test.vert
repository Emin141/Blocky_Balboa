#version 400

uniform mat4 mvp;

layout(location=0) in vec3 vertex_position;
layout(location=1) in vec3 vertex_color;

out vec3 color;

void main() {
    gl_Position = mvp * vec4(vertex_position, 1.0f);
    color = vertex_color;
}