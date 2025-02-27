#include "loader.hpp"
#include "textureLoader.hpp"
#include <iostream>

RawModel Loader::loadToVAO(const std::vector<float> &positions,
                           const std::vector<int> &indices,
                           const std::vector<float> &texCoords) {
  int vaoID = createVAO();
  bindIndicesBuffer(indices);
  storeDataInAttribList(0, positions, 3);
  storeDataInAttribList(1, texCoords, 2);
  unbindVAO();
  int vertexCount = indices.size();
  return RawModel(vaoID, vertexCount);
}

int Loader::createVAO() {
  GLuint vaoID;
  glGenVertexArrays(1, &vaoID);
  glBindVertexArray(vaoID);
  vaos.push_back(vaoID); // Add to VAOs list
  return vaoID;
}
void Loader::storeDataInAttribList(int attribNumber,
                                   const std::vector<float> &data,
                                   int coordSize) {
  GLuint vboID;
  glGenBuffers(1, &vboID);
  glBindBuffer(GL_ARRAY_BUFFER, vboID);
  // Upload the positions data to the VBO
  glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(),
               GL_STATIC_DRAW);

  // Set the vertex attribute pointer
  glVertexAttribPointer(attribNumber, coordSize, GL_FLOAT, GL_FALSE, 0,
                        (void *)0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  vbos.push_back(vboID); // Add to VBOs list
}

void Loader::unbindVAO() { glBindVertexArray(0); }
void Loader::bindIndicesBuffer(const std::vector<int> &indices) {
  GLuint vboID;
  glGenBuffers(1, &vboID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int),
               indices.data(), GL_STATIC_DRAW);
  vbos.push_back(vboID);
}

int Loader::loadTexture(std::string path) {
  // Load a texture
  GLuint textureID = TextureLoader::loadTexture(path);
  if (textureID == 0) {
    std::cerr << "Failed to load texture!" << std::endl;
    return -1;
  }
  textures.push_back(textureID);
  return textureID;
}

void Loader::cleanup() {
  // Delete all VAOs
  for (GLuint vao : vaos) {
    glDeleteVertexArrays(1, &vao);
  }

  // Delete all VBOs
  for (GLuint vbo : vbos) {
    glDeleteBuffers(1, &vbo);
  }
  // Delete all textures
  for (GLuint tex : textures) {
    glDeleteTextures(1, &tex);
  }

  // Clear the lists (optional but good practice)
  vaos.clear();
  vbos.clear();
  textures.clear();
}
