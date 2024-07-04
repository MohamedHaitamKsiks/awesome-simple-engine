#version 450

layout(location = 0) in vec4 MODULATE;
layout(location = 0) out vec4 FragColor;

void main() {
    FragColor = MODULATE;
}
