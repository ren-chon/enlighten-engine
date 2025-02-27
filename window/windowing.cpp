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
  //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE); // Use compatibility profile

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
}

void DisplayManager::updateDisplay() {
  // Swap buffers (double buffering)
  glfwSwapBuffers(window);

  // Poll for events (e.g., input, window resize)
  glfwPollEvents();
}

void DisplayManager::closeDisplay() {
  // Clean up and close the window
  glfwDestroyWindow(window);
  glfwTerminate();
}
