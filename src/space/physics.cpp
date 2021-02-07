#include "space/physics.h"

#include <random>
#include <boost/log/trivial.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "engine/core/serializejson.h"
#include "engine/core/json_utils.h"


void space::PhysicsArchetype::deserialize(const Json::Value &)
{
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
    _entities.emplace(entityId, PhysicsEntity());

    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(-100, 100);

    int x = uniform_dist(e1);
    int y = uniform_dist(e1);
    int z = uniform_dist(e1);

    glm::mat4 transform = glm::translate(glm::mat4(1.0),
                                         glm::vec3(x, y, z));

    onTransform().emit(entityId, transform);
  }
}

engine::Signal<engine::EntityId, glm::mat4> & space::Physics::onTransform()
{
  return _transformSignal;
}
