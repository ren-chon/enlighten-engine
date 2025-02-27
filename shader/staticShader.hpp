#pragma once
#include "shader.hpp"

class StaticShader : public ShaderProgram {
private:
  int transformationMatrixLocation;

protected:
  void bindAttributes() override;
  void locateAllUniformLocations() override;

public:
  StaticShader();
  void LoadTransformationMatrix(glm::mat4 matrix) {
    loadMat4(transformationMatrixLocation, matrix);
  }
};
