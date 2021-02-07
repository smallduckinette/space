#ifndef __SPACE_PHYSICS_H__
#define __SPACE_PHYSICS_H__

#include <unordered_map>
#include <glm/glm.hpp>

#include "engine/entity/system.h"
#include "engine/entity/signal.h"
#include "engine/entity/entityid.h"

namespace space
{
  class PhysicsArchetype
  {
  public:
    void deserialize(const Json::Value & doc);

    auto operator<=>(const PhysicsArchetype &) const = default;
  };

  class Physics : public engine::System
  {
  public:
    /// Register an archetype from json
    void registerArchetype(const std::string & name, const Json::Value & doc) override;

    /// Register an archetype from structure
    void registerArchetype(const std::string & name, const PhysicsArchetype & archetype);

    /// Create the entity from the archetype
    void createEntity(engine::EntityId entityId, const std::string & archetype) override;

    /// Entity move signal
    engine::Signal<engine::EntityId, glm::mat4> & onTransform();

  private:
    /// The physics state of an entity
    class PhysicsEntity
    {
    };

    engine::Signal<engine::EntityId, glm::mat4> _transformSignal;

    /// Archetypes
    std::unordered_map<std::string, PhysicsArchetype> _archetypes;

    /// Entities
    std::unordered_map<engine::EntityId, PhysicsEntity> _entities;
  };
}

#endif
