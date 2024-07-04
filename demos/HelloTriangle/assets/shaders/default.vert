#version 450

//attribute
layout(location = 0) in vec2 v_Position;
layout(location = 1) in vec4 v_Modulate;

// outs
layout(location = 0) out vec4 MODULATE;

// main function is generated
void main() {
    MODULATE = v_Modulate;
    gl_Position = vec4(vec3(v_Position, 0.0), 1.0);
}
