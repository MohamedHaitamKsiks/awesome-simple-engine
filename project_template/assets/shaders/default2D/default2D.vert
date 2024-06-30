#version 450

//vertex rate
layout(location = 0) in vec2 v_Position;

//instance rate
layout(location = 1) in vec2 i_Size;
layout(location = 2) in vec2 i_TopLeft;
layout(location = 3) in vec2 i_BottomRight;
layout(location = 4) in vec4 i_Modulate;
layout(location = 5) in mat3 i_Transform;

// outs
layout(location = 0) out vec2 UV;
layout(location = 1) out vec4 MODULATE;

// view position
layout(binding = 0) uniform Render
{
    mat3 Viewport;
    mat3 Camera;
} render;

// main function is generated
void main() 
{
    // send data to frag
    UV = v_Position * i_BottomRight + i_TopLeft; // get uv
    MODULATE = i_Modulate;

    // get vertex position
    vec3 vertex =  vec3(v_Position * i_Size, 0.0) * i_Transform;
    
    // apply viewport and camera transforms
    gl_Position = vec4(vertex * render.Camera * render.Viewport, 1.0);
}
