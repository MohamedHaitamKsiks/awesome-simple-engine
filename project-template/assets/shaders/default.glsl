
varying vec2 UV;
varying vec4 MODULATE;

// vertex code
#ifdef VERTEX

//attribute
attribute vec2 v_Position;
attribute vec2 v_TextureCoord;
attribute vec4 v_Modulate;

//uniform transform
uniform mat3 u_View;
uniform mat3 u_Camera;

// main function is generated
void main(void) 
{
    UV = v_TextureCoord;
    MODULATE = v_Modulate;

    gl_Position = vec4( u_View * u_Camera * vec3(v_Position, 0.0), 1.0);
}

#endif  

// fragment code
#ifdef FRAGMENT

uniform sampler2D u_Texture;

void main(void) 
{
    gl_FragColor = texture2D(u_Texture, UV) * MODULATE;
}

#endif

