#include "camera.hpp"

void Camera::move(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    position.z -= -0.02f;
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    position.x += 0.02f;
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    position.x -= 0.02f;
  }
}