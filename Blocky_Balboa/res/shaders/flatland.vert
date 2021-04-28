#version 330 core

uniform mat4 mvp;
uniform mat4 model_matrix;

layout(location=0) in vec3 a_pos;

void main() {
    gl_Position = mvp*model_matrix*vec4(a_pos, 1.0f);
}