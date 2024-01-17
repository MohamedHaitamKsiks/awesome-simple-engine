#version 450

//attribute
layout(location = 0) in vec2 v_Position;
layout(location = 1) in vec2 v_TextureCoord;
layout(location = 2) in vec4 v_Modulate;

// outs
layout(location = 0) out vec2 UV;
layout(location = 1) out vec4 MODULATE;
    
//uniform transform
layout(binding = 0) uniform Render
{
    mat3 Projection;
    mat3 View;
} render;

// main function is generated
void main() {
    UV = v_TextureCoord;
    MODULATE = v_Modulate;

    gl_Position = vec4(render.Projection * render.View * vec3(v_Position, 0.0f), 1.0f);
}
