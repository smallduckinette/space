#ifndef __SPACE_WORLD_H__
#define __SPACE_WORLD_H__

#include "engine/entity/entitylibrary.h"
#include "engine/graphics/graphics.h"
#include "engine/controls/controls.h"
#include "space/physics.h"

namespace space
{
  class World
  {
  public:
    World(engine::Clock * clock,
          int resX,
          int resY,
          const std::filesystem::path & dataDir);

    /// Process an event
    void onEvent(const SDL_Event & event);

    /// Process the world and display it
    void onFrame(float deltaTs);

  private:
    /// Register all the subsystems, and register all the entities
    void registerSystemsAndEntities();

    /// Create the world and its elements
    void initWorld();

    engine::EntityLibrary _entityLibrary;
    engine::Graphics _graphics;
    engine::Controls _controls;
    Physics _physics;
    std::filesystem::path _dataDir;

    engine::EntityId _selfEntityId;

    const engine::Controls::BindingId _yaw;
    const engine::Controls::BindingId _roll;
    const engine::Controls::BindingId _pitch;
    const engine::Controls::BindingId _throttle;
  };
}

#endif
