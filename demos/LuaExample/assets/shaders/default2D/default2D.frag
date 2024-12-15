#version 450

layout(location = 0) in vec2 UV;
layout(location = 1) in vec4 MODULATE;

layout(location = 0) out vec4 FragColor;

layout(binding = 1) uniform sampler2D Texture;

void main() 
{
    FragColor = texture(Texture, UV) * MODULATE;
}
