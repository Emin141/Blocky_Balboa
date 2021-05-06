#version 330 core

in vec2 var_tex_coords;

uniform sampler2D texture0;

out vec4 frag_color;

void main() {
    frag_color = texture(texture0, var_tex_coords);
}