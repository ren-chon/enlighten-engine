#include "OBJLoader.hpp"
#include <iostream>

RawModel OBJLoader::loadObjModel(std::string filePath, Loader loader) {
  std::vector<float> verticesArray;
  std::vector<float> textureArray;
  std::vector<float> normalsArray;
  std::vector<int> indicesArray;

  // Create an instance of the Assimp importer
  Assimp::Importer importer;

  // Import the model with some postprocessing
  const aiScene *scene = importer.ReadFile(
      filePath,
      aiProcess_Triangulate |             // Triangulate polygons
          aiProcess_GenSmoothNormals |    // Generate normals if not present
          aiProcess_FlipUVs |             // Flip texture coordinates
          aiProcess_JoinIdenticalVertices // Join identical vertices
  );

  // Check if import failed
  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
      !scene->mRootNode) {
    std::cerr << "ERROR: Assimp could not load model: "
              << importer.GetErrorString() << std::endl;
    // Return an empty model
    return loader.loadToVAO(std::vector<float>(), std::vector<int>(),
                            std::vector<float>(), std::vector<float>());
  }

  // We'll assume the model has only one mesh (most OBJ files for simple models
  // do) If your models have multiple meshes, you'd need to iterate through them
  if (scene->mNumMeshes < 1) {
    std::cerr << "ERROR: Model has no meshes" << std::endl;
    return loader.loadToVAO(std::vector<float>(), std::vector<int>(),
                            std::vector<float>(), std::vector<float>());
  }

  // Get the first mesh
  aiMesh *mesh = scene->mMeshes[0];

  // Process vertices
  for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
    // Vertices
    verticesArray.push_back(mesh->mVertices[i].x);
    verticesArray.push_back(mesh->mVertices[i].y);
    verticesArray.push_back(mesh->mVertices[i].z);

    // Texture coordinates (if they exist)
    if (mesh->mTextureCoords[0]) {
      textureArray.push_back(mesh->mTextureCoords[0][i].x);
      textureArray.push_back(
          1.0f - mesh->mTextureCoords[0][i].y); // Flip Y to match original code
    } else {
      textureArray.push_back(0.0f);
      textureArray.push_back(0.0f);
    }

    // Normals (if they exist)
    if (mesh->mNormals) {
      normalsArray.push_back(mesh->mNormals[i].x);
      normalsArray.push_back(mesh->mNormals[i].y);
      normalsArray.push_back(mesh->mNormals[i].z);
    }
  }

  // Process indices
  for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
    aiFace face = mesh->mFaces[i];
    // Assimp triangulates the mesh if we used aiProcess_Triangulate
    for (unsigned int j = 0; j < face.mNumIndices; j++) {
      indicesArray.push_back(face.mIndices[j]);
    }
  }

  // Return the model data using your loader
  return loader.loadToVAO(verticesArray, indicesArray, textureArray,
                          normalsArray);
}
void OBJLoader::processVertex(std::vector<std::string> vertexData,
                              std::vector<int> &indices,
                              std::vector<glm::vec2> &textures,
                              std::vector<glm::vec3> &normals,
                              std::vector<float> &textureArray,
                              std::vector<float> &normalsArray) {}

bool OBJLoader::isIndexValid(int index, int size) {
  return index >= 0 && index < size;
}
// Helper function to split strings (add to OBJLoader class)
std::vector<std::string> OBJLoader::splitString(const std::string &str,
                                                char delimiter) {
  std::vector<std::string> tokens;
  std::stringstream ss(str);
  std::string token;
  while (std::getline(ss, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}