#version 450

//vertex rate
layout(location = 0) in vec2 v_Position;
layout(location = 1) in vec2 v_TextureCoord;

layout(location = 0) out vec2 UV;

// main function is generated
void main() 
{
    UV = v_TextureCoord;
    // apply viewport and camera transforms
    gl_Position = vec4(vec3(v_Position, 1.0), 1.0);
}
