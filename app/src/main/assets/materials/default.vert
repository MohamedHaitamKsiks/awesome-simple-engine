//attribute
attribute vec2 vPosition;
attribute vec2 vTextureCoord;

//uniforms
uniform mat3 uView;
uniform mat3 uTransform;

//varyings
varying vec2 uv;

//vertex shader
void main()
{
    vec3 position = vec3(vPosition, 1.0);
    gl_Position = vec4(uView * uTransform * position, 1.0);
    uv = vTextureCoord;
}