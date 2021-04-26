#version 400

uniform sampler2D texture0;

in vec3 color;
in vec2 tex_coords;

out vec4 frag_color;

void main() {
    //fragColor = vec4(color, 0.5f);
    frag_color = texture(texture0, tex_coords);
}