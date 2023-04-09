//attribute
attribute vec2 vPosition;
attribute vec2 vTextureCoord;
attribute float vZIndex;
attribute vec4 vModulate;

//uniform transform
uniform mat3 view;
uniform mat3 camera;

//varyings
varying vec2 uv;
varying vec4 modulate;

//bound value from 0.0f -> infinity to 0.0f -> 1.0f
float bound(float x) {
    return 1.0 - 1.0 / ( 1.0 + x / 10.0 );
}

//vertex shader
void main() {
    vec3 position = view * camera * vec3(vPosition, 1.0);
    position.z = 1.0 - bound(vZIndex + 1.0);
    gl_Position = vec4( position, 1.0);
    uv = vTextureCoord ;
    modulate = vModulate;
}