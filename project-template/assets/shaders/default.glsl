//vertex code
#ifdef VERTEX

//attribute
in vec2 v_Position;
in vec2 v_TextureCoord;
in vec4 v_Modulate;

// outs
out vec2 UV;
out vec4 MODULATE;

//uniform transform
uniform mat3 u_View;
uniform mat3 u_Camera;

// main function is generated
void main() 
{
    UV = v_TextureCoord;
    MODULATE = v_Modulate;

    gl_Position = vec4( u_View * u_Camera * vec3(v_Position, 0.0), 1.0);
}

#endif  

// fragment code
#ifdef FRAGMENT

in vec2 UV;
in vec4 MODULATE;

out vec4 fragColor;

uniform sampler2D u_Texture;

void main() 
{
    fragColor = texture(u_Texture, UV) * MODULATE;
}

#endif

