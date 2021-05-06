#version 330 core

layout(location=0) in vec3 a_position;
layout(location=1) in vec2 a_tex_coords;
layout(location=2) in vec3 a_normal;

uniform mat4 model_matrix;
uniform mat4 mvp;

out vec2 var_tex_coords;

void main() {
    var_tex_coords = a_tex_coords;
    vec3 temp_normal = a_normal;
    gl_Position = mvp * model_matrix * vec4(a_position, 1.0f);
}