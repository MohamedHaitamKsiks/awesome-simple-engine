#version 450

layout(location = 0) in vec2 UV;
layout(location = 1) in vec4 MODULATE;

layout(location = 0) out vec4 FragColor;

layout(binding = 1) uniform sampler2D Texture;

void main() 
{
    vec4 color = texture(Texture, UV) * MODULATE;
    FragColor = vec4(1.0f, 1.0f, 1.0f, color.a);

}
