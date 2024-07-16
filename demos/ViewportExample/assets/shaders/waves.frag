#version 450

layout(location = 0) in vec2 UV;
layout(location = 0) out vec4 FragColor;

layout(binding = 1) uniform sampler2D ScreenTexture; 
layout(binding = 2) uniform sampler2D WavesTexture;
layout(binding = 0) uniform Waver
{
    float Time;
    vec2 Pos;
} waver;

float pinch(float t)
{
    return exp(-pow(t, 2.0) / 0.03 );
}

void main() 
{
    float pinched = pinch(length(UV - waver.Pos));
    vec4 waveOffset = texture(WavesTexture, UV + waver.Time * 0.1f);

    FragColor = texture(ScreenTexture, UV + waveOffset.rg * 0.08f * pinched) * (0.8 + 0.2 * pinched);
}
