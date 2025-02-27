#pragma once
#include "../includes/glad/glad.h"
#include "model.hpp"
#include <GL/gl.h>
#include <GL/glext.h>
#include <string>
#include <vector>

class Loader {
public:
  RawModel loadToVAO(const std::vector<float> &positions,
                     const std::vector<int> &indices,
                     const std::vector<float> &texCoords);

  void cleanup();
  int loadTexture(std::string fileName);

private:
  std::vector<GLuint> vaos;
  std::vector<GLuint> vbos;
  std::vector<GLuint> textures;
  int createVAO();
  void storeDataInAttribList(int attribNumber, const std::vector<float> &data,
                             int coordSize);
  void unbindVAO();
  void bindIndicesBuffer(const std::vector<int> &indices);
};