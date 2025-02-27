#version 400 core

in vec3 position;

in vec2 textureCoords;

// out to frag shader
out vec2 passTextureCoords;

uniform mat4 transformationMatrix;

void main() {
    // where in screen the vertex should be rendered by setting this
    gl_Position = transformationMatrix * vec4(position, 1.0);
    // textcoords get linearly intrpolated all  over the quad tobe  used in frag shader
    passTextureCoords = textureCoords;
}