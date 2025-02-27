#pragma once
#include "../includes/glad/glad.h"
#include <GL/gl.h>
#include <GL/glext.h>
#include <string>

class TextureLoader {
public:
    // Load a texture from a file and return its OpenGL texture ID
    static GLuint loadTexture(const std::string& filePath);

    // Clean up a texture
    static void deleteTexture(GLuint textureID);

private:
    // Flip the image vertically (stb_image loads images upside-down by default)
    static void flipImageVertically(unsigned char* image, int width, int height, int channels);
};
