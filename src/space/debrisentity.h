#ifndef __SPACE_DEBRISENTITY_H__
#define __SPACE_DEBRISENTITY_H__

#include <glm/glm.hpp>

namespace space
{
  class DebrisEntity
  {
  public:
    DebrisEntity(const glm::vec3 & position,
                 const glm::vec3 & rotationAxis,
                 float rotationSpeed);

    glm::mat4 update(float deltaTs);

  private:
    const glm::vec3 _rotationAxis;
    const float _rotationSpeed;

    glm::mat4 _transform;
  };
}

#endif
