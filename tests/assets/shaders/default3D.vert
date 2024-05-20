#version 450

//attribute
layout(location = 0) in vec3 v_Position;
layout(location = 1) in vec3 v_Normal;
layout(location = 2) in vec2 v_TextureCoord;
layout(location = 3) in vec4 v_Modulate;
layout(location = 4) in mat4 i_Transform; // instance transform

// outs
layout(location = 0) out vec2 UV;
layout(location = 1) out vec3 NORMAL;
layout(location = 2) out vec3 POSITION;
layout(location = 3) out vec4 MODULATE;

// uniform transform
layout(binding = 0) uniform Render
{
    mat4 Model;
    mat4 View;
    mat4 Projection;
} render;

layout(binding = 1) uniform sampler2D Texture;

// main function is generated
void main() {
    mat4 transform = i_Transform;

    UV = v_TextureCoord;
    MODULATE = v_Modulate;
    NORMAL = mat3(transpose(inverse(transform))) * v_Normal;
    POSITION = vec3(transform * vec4(v_Position, 1.0));

    gl_Position = render.Projection * render.View * transform * vec4(v_Position, 1.0);
}
