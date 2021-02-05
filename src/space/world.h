#ifndef __SPACE_WORLD_H__
#define __SPACE_WORLD_H__

#include "engine/entity/entitylibrary.h"
#include "engine/graphics/graphics.h"

namespace space
{
  class World
  {
  public:
    World(engine::Clock * clock,
          int resX,
          int resY,
          const std::filesystem::path & dataDir);

    void onFrame();

  private:
    /// Register all the subsystems, and register all the entities
    void registerSystemsAndEntities();

    /// Create the world and its elements
    void initWorld();

    engine::EntityLibrary _entityLibrary;
    engine::Graphics _graphics;
    std::filesystem::path _dataDir;
  };
}

#endif
