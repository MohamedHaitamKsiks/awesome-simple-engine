//vertex code
#ifdef VERTEX

//attribute
layout(location = 0) in vec3 v_Position;
layout(location = 1) in vec3 v_Normal;
layout(location = 2) in vec2 v_TextureCoord;
layout(location = 3) in vec4 v_Modulate;
layout(location = 4) in mat4 i_Transform; // instance transform

// outs
out vec2 UV;
out vec3 NORMAL;
out vec3 POSITION;
out vec4 MODULATE;

// uniform transform
uniform mat4 u_Projection;
uniform mat4 u_Camera;
uniform mat4 u_Transform;

// main function is generated
void main() {
    mat4 transform = i_Transform;

    UV = v_TextureCoord;
    MODULATE = v_Modulate;
    NORMAL = mat3(transpose(inverse(transform))) * v_Normal;
    POSITION = vec3(transform * vec4(v_Position, 1.0f));

    gl_Position = u_Projection * u_Camera * transform * vec4(v_Position, 1.0f);
}

#endif  

// fragment code
#ifdef FRAGMENT

in vec2 UV;
in vec4 MODULATE;
in vec3 NORMAL;
in vec3 POSITION;

out vec4 fragColor;

void main() {
    fragColor = MODULATE;
}

#endif
