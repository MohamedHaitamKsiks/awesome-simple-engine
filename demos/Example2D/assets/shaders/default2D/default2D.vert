#version 450

//vertex rate
layout(location = 0) in vec2 v_Position;
layout(location = 1) in vec2 v_TextureCoord;
layout(location = 2) in vec4 v_Modulate;

// out
layout(location = 0) out vec2 UV;
layout(location = 1) out vec4 MODULATE;

// rendering 2d data
layout(binding = 0) uniform Renderer2D
{
    mat3 CameraTransform;
    mat3 ViewportTransform;
} renderer2D;

// main function is generated
void main()
{
    UV = v_TextureCoord;
    MODULATE = v_Modulate;

    // get position
    vec3 screenPosition = renderer2D.ViewportTransform * inverse(renderer2D.CameraTransform) * vec3(v_Position, 1.0);

    // apply viewport and camera transforms
    gl_Position = vec4(screenPosition, 1.0);
}
