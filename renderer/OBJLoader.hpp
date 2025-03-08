#pragma once
#include "../model/loader.hpp"
#include <algorithm>
#include <fstream>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
class OBJLoader {
public:
  RawModel loadObjModel(std::string filePath, Loader loader);
  void processVertex(std::vector<std::string> vertexData,
                     std::vector<int> &indices,
                     std::vector<glm::vec2> &textures,
                     std::vector<glm::vec3> &normals,
                     std::vector<float> &textureArray,
                     std::vector<float> &normalsArray);
  std::vector<std::string> splitString(const std::string &str, char delimiter);
  bool isIndexValid(int index, int size);
};