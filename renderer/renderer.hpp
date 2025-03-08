#pragma once
#include "../entities/entity.hpp"
#include "../includes/glad/glad.h"
#include "../model/model.hpp"
#include "../model/texturedModel.hpp"
#include "../shader/staticShader.hpp"
#include "../window/windowing.hpp"
#include <GL/gl.h>
#include <GL/glext.h>

class Renderer {
private:
  glm::mat4 projectionMatrix;
  float FOV = 70;
  float NEAR_PLANE = 0.1f;
  float FAR_PLANE = 100.0f;

  void createProjectionMatrix();

public:
   Renderer(StaticShader shader) {
    createProjectionMatrix();
    shader.start();
    shader.LoadProjectionMatrix(projectionMatrix);
    shader.stop();
  }
  void prepare();
  void render(Entity entity, StaticShader shader);
};