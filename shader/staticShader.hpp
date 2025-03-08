#pragma once
#include "shader.hpp"
#include "../entities/camera.hpp"
#include "../toolbox/maths.hpp"
#include "../entities/Light.hpp"
class StaticShader : public ShaderProgram {
private:
  int transformationMatrixLocation;
  int projectionMatrixLocation;
  int viewMatrixLocation;
  int lightPositionLocation;
  int lightColorLocation;

protected:
  void bindAttributes() override;
  void locateAllUniformLocations() override;

public:
  StaticShader();
  void LoadTransformationMatrix(glm::mat4 matrix) {
    loadMat4(transformationMatrixLocation, matrix);
  }
  void LoadProjectionMatrix(glm::mat4 projection);
  void LoadViewMatrix(Camera cam);

  void loadLight(Light light);
};
