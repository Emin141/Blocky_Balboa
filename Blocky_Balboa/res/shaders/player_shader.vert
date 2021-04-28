#version 330 core

uniform mat4 mvp;
uniform mat4 model_matrix;

layout(location=0) in vec3 vertex_position;

void main() {
    gl_Position = mvp * model_matrix * vec4(vertex_position, 1.0f);
}