#version 450

layout(location = 0) in vec2 UV;
layout(location = 0) out vec4 FragColor;

void main() 
{
    FragColor = vec4(1.0, UV.x, UV.y, 1.0);
}