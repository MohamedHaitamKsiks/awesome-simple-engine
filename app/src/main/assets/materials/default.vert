//attribute
attribute vec2 vPosition;
attribute vec2 vTextureCoord;

//uniforms
uniform mat3 view;
uniform mat3 transform;

//varyings
varying vec2 uv;

//vertex shader
void main() {
    gl_Position = vec4(vec3(vPosition, 1.0), 1.0);
    uv = vec2(vTextureCoord.x, 1.0 - vTextureCoord.y);
}
