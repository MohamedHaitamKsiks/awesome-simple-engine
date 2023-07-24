// vertex part
#ifdef VERTEX

//attribute
attribute vec2 v_Position;
attribute vec2 v_TextureCoord;
attribute vec4 v_Modulate;

//uniform transform
uniform mat3 u_View;
uniform mat3 u_Camera;

// variants
varying vec4 COLOR;
varying vec2 UV;

void main(void) 
{
    UV = v_TextureCoord;
    COLOR = v_Modulate;

    gl_Position = vec4( u_View * u_Camera * vec3(v_Position, 0.0), 1.0);
}

#endif

// shader part
#ifdef FRAGMENT

varying vec4 COLOR;
varying vec2 UV;

uniform sampler2D u_Texture;

void main(void) 
{
    gl_FragColor = texture2D(u_Texture, UV) * COLOR;
}

#endif

