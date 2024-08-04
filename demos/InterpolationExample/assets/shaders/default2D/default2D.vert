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
    int PixelSnapping;
} renderer2D;

// main function is generated
void main()
{
    UV = v_TextureCoord;
    MODULATE = v_Modulate;

    // get position relative to camera
    vec3 cameraPosition = inverse(renderer2D.CameraTransform) * vec3(v_Position, 1.0);
    // snap vertices to pixel grid if pixel snapping is enabled
    if (renderer2D.PixelSnapping != 0)
    {
        cameraPosition = ivec3(cameraPosition);
    }

    // get position relative to screen coordinates
    vec3 screenPosition = renderer2D.ViewportTransform * cameraPosition;

    // apply viewport and camera transforms
    gl_Position = vec4(screenPosition, 1.0);
}
