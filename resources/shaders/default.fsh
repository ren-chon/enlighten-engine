#version 400 core

// input of frag is out from vertex shader, same name and type
in vec3 color;

out vec4 outColor;

void main() {
    // set the interpolated color to scr
    outColor = vec4(color, 1.0);
}