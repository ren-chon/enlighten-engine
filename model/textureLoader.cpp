#include "textureLoader.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h" // Include stb_image.h for loading image files
#include <iostream>

GLuint TextureLoader::loadTexture(const std::string& filePath) {
    // Load the image using stb_image
    int width, height, channels;
    unsigned char* image = stbi_load(filePath.c_str(), &width, &height, &channels, 0);
    if (!image) {
        std::cerr << "Failed to load texture: " << filePath << std::endl;
        return 0;
    }

    // Flip the image vertically (OpenGL expects the origin at the bottom-left)
    flipImageVertically(image, width, height, channels);

    // Generate and bind a texture object
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Determine the format based on the number of channels
    GLenum format = GL_RGB;
    if (channels == 4) {
        format = GL_RGBA;
    } else if (channels == 1) {
        format = GL_RED;
    }

    // Upload the image data to the texture
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Free the image data
    stbi_image_free(image);

    // Unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0);

    return textureID;
}

void TextureLoader::deleteTexture(GLuint textureID) {
    glDeleteTextures(1, &textureID);
}

void TextureLoader::flipImageVertically(unsigned char* image, int width, int height, int channels) {
    for (int y = 0; y < height / 2; ++y) {
        for (int x = 0; x < width; ++x) {
            for (int c = 0; c < channels; ++c) {
                unsigned char top = image[(y * width + x) * channels + c];
                unsigned char bottom = image[((height - 1 - y) * width + x) * channels + c];
                image[(y * width + x) * channels + c] = bottom;
                image[((height - 1 - y) * width + x) * channels + c] = top;
            }
        }
    }
}