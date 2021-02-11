#include "space/shipentity.h"

#include <boost/log/trivial.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/euler_angles.hpp>


space::ShipEntity::ShipEntity(float power):
  _power(power),
  _yawDelta(0),
  _rollDelta(0),
  _pitchDelta(0),
  _throttle(0),
  _rotate(1),
  _position(0, 0, 0)
{
}

void space::ShipEntity::setYawDelta(float val)
{
  _yawDelta = val;
}

void space::ShipEntity::setRollDelta(float val)
{
  _rollDelta = val;
}

void space::ShipEntity::setPitchDelta(float val)
{
  _pitchDelta = val;
}

void space::ShipEntity::setThrottle(float val)
{
  _throttle = val;
}

glm::mat4 space::ShipEntity::update(float deltaTs)
{
  // Adjust attitude
  _rotate *= glm::eulerAngleYXZ(_yawDelta * deltaTs,
                                _pitchDelta * deltaTs,
                                _rollDelta * deltaTs);

  // Adjust position
  glm::vec3 front(0, 0, 1);
  glm::vec3 up(0, 1, 0);
  _position +=
    (glm::mat3(_rotate) * front) *
    _power * deltaTs * _throttle;

  return glm::lookAt(_position,
                     _position + glm::mat3(_rotate) * front,
                     glm::mat3(_rotate) * up);
}
