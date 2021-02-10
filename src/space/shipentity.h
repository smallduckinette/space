#ifndef __SPACE_SHIPENTITY_H__
#define __SPACE_SHIPENTITY_H__

#include <glm/glm.hpp>

namespace space
{
  /// The physics state of an entity
  class ShipEntity
  {
  public:
    ShipEntity(float power = 100);

    void setYawDelta(float val);
    void setRollDelta(float val);
    void setPitchDelta(float val);
    void setThrottle(float val);

    glm::mat4 update(float deltaTs);

  private:
    const float _power;

    float _yawDelta;
    float _rollDelta;
    float _pitchDelta;
    float _throttle;

    glm::mat4 _rotate;
    glm::vec3 _position;
  };
}

#endif
