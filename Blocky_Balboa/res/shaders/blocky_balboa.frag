#version 330 core

uniform sampler2D texture0;

in vec3 color;
in vec2 tex_coords;

out vec4 frag_color;

void main() {
    frag_color = texture(texture0, tex_coords) / vec4(color, 1.0f);
}