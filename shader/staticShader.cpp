#include "staticShader.hpp"

StaticShader::StaticShader()
    : ShaderProgram("resources/shaders/default.vsh",
                    "resources/shaders/default.fsh") {
  linkProgram(); // Link AFTER attributes are bound
}

void StaticShader::bindAttributes() {
  bindAttribute(0, "position"); // Bind attribute 0 to "position"
  bindAttribute(1, "textureCoords");
  bindAttribute(2, "normal");
}
void StaticShader::locateAllUniformLocations() {
  transformationMatrixLocation = locateUniform("transformationMatrix");
  projectionMatrixLocation = locateUniform("projectionMatrix");
  viewMatrixLocation = locateUniform("viewMatrix");
  lightPositionLocation = locateUniform("lightPosition");
  lightColorLocation = locateUniform("lightColor");
}

void StaticShader::LoadProjectionMatrix(glm::mat4 projection) {
  loadMat4(projectionMatrixLocation, projection);
}
void StaticShader::LoadViewMatrix(Camera cam) {
  Maths meth;
  glm::mat4 viewMatrix = meth.createViewMatrix(cam);
  loadMat4(viewMatrixLocation, viewMatrix);
}
void StaticShader::loadLight(Light light) {
  loadVector(lightPositionLocation, light.getPosition());
  loadVector(lightColorLocation, light.getColor());
}
