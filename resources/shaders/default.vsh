#version 400 core

in vec3 position;

out vec3 color;

void main() {
    // where in screen the vertex should be rendered by setting this
    gl_Position = vec4(position, 1.0);
    // set color based on position of that vertex
    color = vec3(position.x + 0.5, 1.0, position.y + 0.5);
}