#version 400 core

// input of frag is out from vertex shader, same name and type
in vec2 passTextureCoords;
in vec3 surfaceNormal;
in vec3 toLightVector;

out vec4 outColor;

// represents the texture
uniform sampler2D textureSampler;
uniform vec3 lightColor;

void main() {
    vec3 unitNormal = normalize(surfaceNormal);
    vec3 unitLightVector = normalize(toLightVector);

    float nDotl = dot(unitNormal, unitLightVector);
    float brightness = max(nDotl, 0.0);
    vec3 diffuse = brightness * lightColor;
    
    // set the color of texture pixels into the quad coords by sampling 2d to those coords of quad
    outColor = vec4(diffuse, 1.0) ;
}