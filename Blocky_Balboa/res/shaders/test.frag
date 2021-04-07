#version 400

//uniform vec4 external_color;
in vec3 color;
out vec4 fragColor;

void main() {
    fragColor = vec4(color, 0.5f);
}