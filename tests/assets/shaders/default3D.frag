#version 450

layout(location = 0) in vec2 UV;
layout(location = 1) in vec3 NORMAL;
layout(location = 2) in vec3 POSITION;
layout(location = 3) in vec4 MODULATE;

layout(location = 0) out vec4 FragColor;

void main() {
    FragColor = MODULATE;
}
