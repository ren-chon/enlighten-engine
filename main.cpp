#include "entities/entity.hpp"
#include "model/loader.hpp"
#include "model/model.hpp"
#include "model/modelTexture.hpp"
#include "model/texturedModel.hpp"
#include "renderer/renderer.hpp"
#include "shader/staticShader.hpp"
#include "window/windowing.hpp"
#include <chrono>
#include <thread>

// Function to cap the FPS to a specified limit



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
  TexturedModel staticModel(model, texture);

  Entity entity(staticModel, glm::vec3(-1.0f, 0.0f, 0.0f), 0, 0, 0, 1);

  // FPS Cap Configuration
  const float FPS_LIMIT = 1.0f; // Target FPS

  // Store the time of the last frame
  double lastFrameTime = glfwGetTime();
  // Main loop
  while (!display.shouldClose()) {

    entity.increasePosition(0.002f, 0, 0);
    entity.increaseRotation(0, 1, 0);
    renderer.prepare();
    shaders.start();
    renderer.render(entity, shaders);
    shaders.stop();
    display.updateDisplay();

    // FPS cap
    display.capFPS(FPS_LIMIT, lastFrameTime);
  }

  shaders.cleanUp();
  loader.cleanup();
  display.closeDisplay();

  return 0;
}
