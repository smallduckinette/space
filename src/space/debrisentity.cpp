#include "space/debrisentity.h"

#include <glm/gtx/transform.hpp>


space::DebrisEntity::DebrisEntity(const glm::vec3 & position,
                                  const glm::vec3 & rotationAxis,
                                  float rotationSpeed):
  _rotationAxis(rotationAxis),
  _rotationSpeed(rotationSpeed),
  _transform(glm::translate(glm::mat4(1), position))
{
}

glm::mat4 space::DebrisEntity::update(float deltaTs)
{
  return _transform = glm::rotate(_transform,
                                  glm::radians(_rotationSpeed) * deltaTs,
                                  _rotationAxis);
}
