#include "staticShader.hpp"

StaticShader::StaticShader()
    : ShaderProgram("resources/shaders/default.vsh",
                    "resources/shaders/default.fsh") {
  linkProgram(); // Link AFTER attributes are bound
}

void StaticShader::bindAttributes() {
  bindAttribute(0, "position"); // Bind attribute 0 to "position"
  bindAttribute(1, "textureCoords");
}
void StaticShader::locateAllUniformLocations() {
  transformationMatrixLocation = locateUniform("transformationMatrix");
}