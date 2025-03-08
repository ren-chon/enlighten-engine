#version 400 core

in vec3 position;
in vec2 textureCoords;
in vec3 normal;

// out to frag shader
out vec2 passTextureCoords;
out vec3 surfaceNormal;
out vec3 toLightVector;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform vec3 lightPosition;

void main() {
    vec4 worldPosition = transformationMatrix * vec4(position, 1);

    // where in screen the vertex should be rendered by setting this
    gl_Position = projectionMatrix * viewMatrix * worldPosition;
    // textcoords get linearly intrpolated all  over the quad tobe  used in frag shader
    passTextureCoords = textureCoords;
    
    surfaceNormal = (transformationMatrix * vec4(normal, 0.0)).xyz;
    toLightVector = lightPosition - worldPosition.xyz;
}