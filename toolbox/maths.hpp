#pragma once
#include "../entities/camera.hpp"
#include <cmath> // For std::radians
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // For glm::translate, glm::rotate, etc.
#include <glm/gtc/type_ptr.hpp>         // For glm::value_ptr
#include <glm/vec3.hpp>                 // For glm::vec3

class Maths {
public:
  glm::mat4 createTransformationMatrix(glm::vec3 translation, float rx,
                                       float ry, float rz, float scale) {
    glm::mat4 matrix = glm::mat4(1.0f);
    matrix = glm::translate(
        matrix, glm::vec3(translation.x, translation.y, translation.z));
    matrix = glm::rotate(matrix, glm::radians(rx), glm::vec3(1.0f, 0.0f, 0.0f));
    matrix = glm::rotate(matrix, glm::radians(ry), glm::vec3(0.0f, 1.0f, 0.0f));
    matrix = glm::rotate(matrix, glm::radians(rz), glm::vec3(0.0f, 0.0f, 1.0f));
    matrix = glm::scale(matrix, glm::vec3(scale, scale, scale));

    return matrix;
  }

  glm::mat4 createViewMatrix(const Camera &camera) {
    // Create an identity matrix
    glm::mat4 viewMatrix = glm::mat4(1.0f);

    // Rotate based on camera pitch (around X-axis)
    float pitch = glm::radians(camera.getPitch()); // Use glm::radians
    viewMatrix = glm::rotate(viewMatrix, pitch, glm::vec3(1.0f, 0.0f, 0.0f));

    // Rotate based on camera yaw (around Y-axis)
    float yaw = glm::radians(camera.getYaw()); // Use glm::radians
    viewMatrix = glm::rotate(viewMatrix, yaw, glm::vec3(0.0f, 1.0f, 0.0f));

    // Translate based on camera position (negative because we move the world,
    // not the camera)
    glm::vec3 cameraPos = camera.getPosition();
    glm::vec3 negativeCameraPos = -cameraPos;
    viewMatrix = glm::translate(viewMatrix, negativeCameraPos);

    return viewMatrix;
  }
};