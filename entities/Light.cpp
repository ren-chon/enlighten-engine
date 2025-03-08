#include "Light.hpp"
glm::vec3 Light::getPosition() const { return position; }
glm::vec3 Light::getColor() const { return position; }

void Light::setPosition(glm::vec3 pos) { position = pos; }
 
void Light::setColor(glm::vec3 clr) { color = clr; }