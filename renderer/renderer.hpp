#pragma once
#include "../includes/glad/glad.h"
#include "../model/model.hpp"
#include "../model/texturedModel.hpp"
#include <GL/gl.h>
#include <GL/glext.h>

class Renderer {
public:
  void prepare();
  void render(TexturedModel tModel);
};