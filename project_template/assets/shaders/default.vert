#version 450

//vertex rate
layout(location = 0) in vec2 v_Position;


// main function is generated
void main() 
{
    // apply viewport and camera transforms
    gl_Position = vec4(vec3(v_Position, 1.0), 1.0);
}
