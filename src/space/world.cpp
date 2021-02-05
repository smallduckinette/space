#include "world.h"

#include <fstream>
#include <random>
#include <boost/log/trivial.hpp>

space::World::World(engine::Clock * clock,
                    int resX,
                    int resY,
                    const std::filesystem::path & dataDir):
  _graphics(clock, resX, resY, dataDir),
  _dataDir(dataDir)
{
  registerSystemsAndEntities();
  initWorld();
  BOOST_LOG_TRIVIAL(info) << "Start";
}

void space::World::onFrame()
{
  _graphics.setView(glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f),
                                glm::vec3(0.0f, 0.0f, 1.0f),
                                glm::vec3(0.0f, 1.0f, 0.0f)));
  _graphics.display();
}

void space::World::registerSystemsAndEntities()
{
  BOOST_LOG_TRIVIAL(info) << "Register systems and archetypes";
  _entityLibrary.registerSystem(&_graphics);

  Json::Value doc;
  std::ifstream str(_dataDir / "archetypes.json");
  str >> doc;
  _entityLibrary.registerArchetypes(doc);
}

void space::World::initWorld()
{
  BOOST_LOG_TRIVIAL(info) << "Create world";
  std::random_device r;
  std::default_random_engine e1(r());
  std::uniform_int_distribution<int> uniform_dist(-100, 100);

  for(int index = 0; index < 1000; ++index)
  {
    engine::EntityId entityId = _entityLibrary.createEntity("asteroid");

    int x = uniform_dist(e1);
    int y = uniform_dist(e1);
    int z = uniform_dist(e1);

    _graphics.setEntityTransform(entityId,
                                 glm::translate(glm::mat4(1.0),
                                                glm::vec3(x, y, z)));
  }
}
