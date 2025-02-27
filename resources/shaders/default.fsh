#version 400 core

// input of frag is out from vertex shader, same name and type
in vec2 passTextureCoords;


out vec4 outColor;

// represents the texture
uniform sampler2D textureSampler;

void main() {
    // set the color of texture pixels into the quad coords by sampling 2d to those coords of quad
    outColor = texture(textureSampler, passTextureCoords);
}