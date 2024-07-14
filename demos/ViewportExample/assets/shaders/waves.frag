#version 450

layout(location = 0) in vec2 UV;
layout(location = 0) out vec4 FragColor;

layout(binding = 1) uniform sampler2D ScreenTexture; 
layout(binding = 2) uniform sampler2D WavesTexture;
layout(std140, binding = 0) uniform Timer
{
    float Time;
} timer;

void main() 
{
    vec4 waveOffset = texture(WavesTexture, UV + vec2(0.5f, 0.5) * timer.Time * 0.2f);
    FragColor = texture(ScreenTexture, UV + waveOffset.rg * 0.08f);
}
