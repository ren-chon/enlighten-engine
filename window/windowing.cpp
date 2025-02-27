#include "windowing.hpp"
#include <iostream>

void DisplayManager::createDisplay() {
  // Initialize GLFW
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return;
  }

  // Set OpenGL version to 3.3 (or whatever version you're targeting)
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE); // Use
  // compatibility profile

  // Create the window
  window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, nullptr, nullptr);
  if (!window) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return;
  }

  // Make the window's context current
  glfwMakeContextCurrent(window);

  // Initialize GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Failed to initialize GLAD" << std::endl;
    return;
  }

  // Set the viewport size
  glViewport(0, 0, WIDTH, HEIGHT);

  // Enable vsync (optional)
  glfwSwapInterval(1);

  logMonitorInfo();
}

void DisplayManager::updateDisplay() {
  // Swap buffers (double buffering)
  glfwSwapBuffers(window);

  // Poll for events (e.g., input, window resize)
  glfwPollEvents();
}
void DisplayManager::logMonitorInfo() {
  GLFWmonitor *monitor = glfwGetPrimaryMonitor();
  const GLFWvidmode *mode = glfwGetVideoMode(monitor);
  std::cout << "Current refresh rate: " << mode->refreshRate << " Hz"
            << std::endl;
}
void DisplayManager::capFPS(float fpsLimit, double &lastTime) {
  double currentTime = glfwGetTime(); // Get the current time (GLFW native time)
  double deltaTime = currentTime - lastTime;

  // Calculate the desired frame time based on the FPS limit
  double frameTimeLimit = 1.0 / fpsLimit;

  // If the frame took longer than the allowed time, just continue
  if (deltaTime < frameTimeLimit) {
    // Calculate the remaining time to sleep
    double sleepTime = frameTimeLimit - deltaTime;
    // Wait using glfwWaitEventsTimeout to limit the FPS
    glfwWaitEventsTimeout(
        sleepTime); // Sleeps the thread for the remaining time
  }

  // Update the last time for the next frame
  lastTime = glfwGetTime();
}
void DisplayManager::closeDisplay() {
  // Clean up and close the window
  glfwDestroyWindow(window);
  glfwTerminate();
}
