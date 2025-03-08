#include "entities/camera.hpp"
#include "entities/entity.hpp"
#include "entities/Light.hpp"
#include "model/loader.hpp"
#include "model/model.hpp"
#include "model/modelTexture.hpp"
#include "model/texturedModel.hpp"
#include "renderer/OBJLoader.hpp"
#include "renderer/renderer.hpp"
#include "shader/staticShader.hpp"
#include "window/windowing.hpp"
#include <chrono>
#include <thread>

// Function to cap the FPS to a specified limit

int main() {
  DisplayManager display;
  Loader loader;
  display.createDisplay();

  StaticShader shaders;
  Renderer renderer(shaders);
  OBJLoader objLoader;
  RawModel model = objLoader.loadObjModel("resources/models/dragon.obj", loader);
  if (model.getVaoID() == 0) {
    std::cerr << "Failed to load model!" << std::endl;
    return -1;
  }
  ModelTexture texture(loader.loadTexture(""));
  TexturedModel staticModel(model, texture);

  Entity entity(staticModel, glm::vec3(0, 0, -20), 0, 0, 0, 1);
Light light(glm::vec3(0, 5, 5), glm::vec3(1, 1, 1)); // Front-top lighting
  Camera camera;
  // FPS Cap Configuration
  const float FPS_LIMIT = 144.0f; // Target FPS

  // Store the time of the last frame
  double lastFrameTime = glfwGetTime();
  GLenum error = glGetError();
  if (error != GL_NO_ERROR) {
    std::cerr << "OpenGL error: " << error << std::endl;
  }
  // Main loop
  while (!display.shouldClose()) {
    entity.increaseRotation(0, 1, 0);
    camera.move(display.getWindow());
    renderer.prepare();
    shaders.start();
    shaders.loadLight(light);
    shaders.LoadViewMatrix(camera);
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
