#ifndef __SPACE_PHYSICS_H__
#define __SPACE_PHYSICS_H__

#include <unordered_map>
#include <glm/glm.hpp>

#include "engine/entity/system.h"
#include "engine/entity/signal.h"
#include "engine/entity/entityid.h"
#include "space/debrisentity.h"
#include "space/shipentity.h"

namespace space
{
  class PhysicsArchetype
  {
  public:
    void deserialize(const Json::Value & doc);

    auto operator<=>(const PhysicsArchetype &) const = default;

    std::string _type;
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

    /// Yaw action on a ship-type entity
    void updateYawAxis(engine::EntityId entityId, double value);

    /// Roll action on a ship-type entity
    void updateRollAxis(engine::EntityId entityId, double value);

    /// Pitch action on a ship-type entity
    void updatePitchAxis(engine::EntityId entityId, double value);

    /// Throttle action on a ship-type entity
    void updateThrottle(engine::EntityId entityId, double value);

    /// Entity move signal
    engine::Signal<engine::EntityId, glm::mat4> & onTransform();

    /// Update
    void update(float deltaTs);

  private:
    engine::Signal<engine::EntityId, glm::mat4> _transformSignal;

    /// Archetypes
    std::unordered_map<std::string, PhysicsArchetype> _archetypes;

    /// Debris
    std::unordered_map<engine::EntityId, DebrisEntity> _debris;

    /// Ships
    std::unordered_map<engine::EntityId, ShipEntity> _ships;
  };
}

#endif
