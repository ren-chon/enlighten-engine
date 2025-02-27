#include "model/loader.hpp"
#include "model/model.hpp"
#include "model/modelTexture.hpp"
#include "model/texturedModel.hpp"
#include "renderer/renderer.hpp"
#include "shader/staticShader.hpp"
#include "window/windowing.hpp"

int main() {
  DisplayManager display;
  Loader loader;
  Renderer renderer;
  display.createDisplay();
  StaticShader shaders;

  std::vector<float> vertices = {
      // left bottom tri
      -0.5f, 0.5f,  0.f, // v0
      -0.5f, -0.5f, 0.f, // v1
      0.5,   -0.5f, 0.f, // v2
      0.5f,  0.5f,  0.f, // v3
  };
  std::vector<int> indices = {
      0, 1, 3, // top left tri v0,v1,v3
      3, 1, 2, // bottom right tri v3,v1,v2
  };
  std::vector<float> textureCoords = {
      0, 0, // v0
      0, 1, // v1
      1, 1, // v2
      1, 0, // v3
  };
  RawModel model = loader.loadToVAO(vertices, indices, textureCoords);
  if (model.getVaoID() == 0) {
    std::cerr << "Failed to load model!" << std::endl;
    return -1;
  }
  ModelTexture texture(loader.loadTexture("resources/textures/akari.jpg"));
  TexturedModel texturedModel(model, texture);
  // Main loop
  while (!display.shouldClose()) {
    renderer.prepare();
    shaders.start();
    renderer.render(texturedModel);
    shaders.stop();
    display.updateDisplay();
  }

  shaders.cleanUp();
  loader.cleanup();
  display.closeDisplay();

  return 0;
}