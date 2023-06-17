

uniform sampler2D texture;
uniform int isSolidColor;

varying vec2 uv;
varying vec4 modulate;

void main() {
    if (isSolidColor == 0)
        gl_FragColor = texture2D(texture, uv) * modulate;
    else
        gl_FragColor = modulate;
}