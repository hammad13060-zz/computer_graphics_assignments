#version 330 core

in vec3 color;
out vec4 choosenColor;

void main() {
    choosenColor = vec4(color, 1.0f);
}
