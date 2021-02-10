#include "space/physics.h"

#include <random>
#include <boost/log/trivial.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "engine/core/serializejson.h"
#include "engine/core/json_utils.h"


void space::PhysicsArchetype::deserialize(const Json::Value & doc)
{
  engine::deserializeJson(_type, doc, "type");
}

void space::Physics::registerArchetype(const std::string & name,
                                       const Json::Value & doc)
{
  const Json::Value * node = engine::getNode(doc, "physics");
  if(node)
  {
    PhysicsArchetype archetype;
    archetype.deserialize(*node);
    registerArchetype(name, archetype);
  }
}

void space::Physics::registerArchetype(const std::string & name,
                                       const PhysicsArchetype & archetype)
{
  _archetypes.emplace(name, archetype);
}

void space::Physics::createEntity(engine::EntityId entityId,
                                  const std::string & archetype)
{
  auto it = _archetypes.find(archetype);
  if(it != _archetypes.end())
  {
    if(it->second._type == "ship")
    {
      _ships.emplace(entityId, ShipEntity());
    }
    else if(it->second._type == "debris")
    {
      std::random_device r;
      std::default_random_engine e1(r());
      std::uniform_real_distribution<float> randomPosition(-100, 100);
      std::uniform_real_distribution<float> randomAxis(-1, 1);
      std::uniform_real_distribution<float> randomRotationSpeed(0, 15);

      float x = randomPosition(e1);
      float y = randomPosition(e1);
      float z = randomPosition(e1);

      float a = randomAxis(e1);
      float b = randomAxis(e1);
      float c = randomAxis(e1);

      float rs = randomRotationSpeed(e1);

      _debris.emplace(entityId, DebrisEntity(glm::vec3(x, y, z),
                                             glm::normalize(glm::vec3(a, b, c)),
                                             rs));
    }
    else
    {
      BOOST_LOG_TRIVIAL(error) << "Unknown physics entity type " << it->second._type;
    }
  }
}

void space::Physics::updateYawAxis(engine::EntityId entityId, double value)
{
  auto it = _ships.find(entityId);
  if(it != _ships.end())
    it->second.setYawDelta(value);
}

void space::Physics::updateRollAxis(engine::EntityId entityId, double value)
{
  auto it = _ships.find(entityId);
  if(it != _ships.end())
    it->second.setRollDelta(value);
}

void space::Physics::updatePitchAxis(engine::EntityId entityId, double value)
{
  auto it = _ships.find(entityId);
  if(it != _ships.end())
    it->second.setPitchDelta(value);
}

void space::Physics::updateThrottle(engine::EntityId entityId, double value)
{
  auto it = _ships.find(entityId);
  if(it != _ships.end())
    it->second.setThrottle(value);
}

engine::Signal<engine::EntityId, glm::mat4> & space::Physics::onTransform()
{
  return _transformSignal;
}

void space::Physics::update(float deltaTs)
{
  for(auto && [id, ship] : _ships)
  {
    onTransform().emit(id, ship.update(deltaTs));
  }

  for(auto && [id, debris] : _debris)
  {
    onTransform().emit(id, debris.update(deltaTs));
  }
}
