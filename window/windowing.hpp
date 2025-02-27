#pragma once
#include "../includes/glad/glad.h"
#include <GL/gl.h>
#include <GL/glext.h>
#include <GLFW/glfw3.h>

class DisplayManager {
private:
  GLFWwindow *window;
  const int WIDTH = 1280;
  const int HEIGHT = 720;
  const char *TITLE = "OpenGL Window";

public:
  void createDisplay();
  void updateDisplay();
  void closeDisplay();
  bool shouldClose() {
    // Check if the window should close (e.g., user clicked the close button)
    return glfwWindowShouldClose(window);
  }
  void capFPS(float fpsLimit, double &lastTime);
  void logMonitorInfo();
};