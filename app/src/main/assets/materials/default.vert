//attribute
attribute vec2 vPosition;
attribute vec2 vTextureCoord;

//uniform transform
uniform mat3 view;
uniform mat3 camera;
uniform mat3 transform;
uniform float zIndex;

//hframes
uniform int hframes;
uniform int hframe;

//vframes
uniform int vframes;
uniform int vframe;

//varyings
varying vec2 uv;

//vertex shader
void main() {
    vec3 position = view * camera * transform * vec3(vPosition, 1.0);
    gl_Position = vec4( position, 1.0);
    uv = vec2((vTextureCoord.x + float(hframe)) / float(hframes), (vTextureCoord.y + float(vframe)) / float(vframes));
}