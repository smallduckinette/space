#include "world.h"

#include <fstream>
#include <boost/log/trivial.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
  BOOST_LOG_TRIVIAL(info) << "Register systems";
  _entityLibrary.registerSystem(&_graphics);
  _entityLibrary.registerSystem(&_physics);

  BOOST_LOG_TRIVIAL(info) << "Register callbacks";
  _physics.onTransform().connect(std::bind(&engine::Graphics::setEntityTransform,
                                           &_graphics,
                                           std::placeholders::_1,
                                           std::placeholders::_2));

  BOOST_LOG_TRIVIAL(info) << "Register entities";
  Json::Value doc;
  std::ifstream str(_dataDir / "archetypes.json");
  str >> doc;
  _entityLibrary.registerArchetypes(doc);
}

void space::World::initWorld()
{
  BOOST_LOG_TRIVIAL(info) << "Create world";
  for(int index = 0; index < 1000; ++index)
  {
    _entityLibrary.createEntity("asteroid");
  }
}
