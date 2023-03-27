precision mediump float;

uniform sampler2D texture;
uniform vec4 modulate;
uniform int isSolidColor;

varying vec2 uv;

void main()
{
    if (isSolidColor != 0)
        gl_FragColor = modulate;
    else
        gl_FragColor = texture2D(texture, uv) * modulate;
}