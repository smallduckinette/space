#include "world.h"

#include <fstream>
#include <boost/log/trivial.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

space::World::World(engine::Clock * clock,
                    int resX,
                    int resY,
                    const std::filesystem::path & dataDir):
  _graphics(clock, resX, resY, dataDir),
  _dataDir(dataDir),
  _yaw(1),
  _roll(2),
  _pitch(3),
  _throttle(4)
{
  registerSystemsAndEntities();
  initWorld();
  BOOST_LOG_TRIVIAL(info) << "Start";
}

void space::World::onEvent(const SDL_Event & event)
{
  _controls.process(event);
}

void space::World::onFrame(float deltaTs)
{
  _physics.update(deltaTs);

  _graphics.display();
}

void space::World::registerSystemsAndEntities()
{
  {
    BOOST_LOG_TRIVIAL(info) << "Register systems";
    _entityLibrary.registerSystem(&_graphics);
    _entityLibrary.registerSystem(&_physics);
  }

  {
    BOOST_LOG_TRIVIAL(info) << "Register inputs";
    Json::Value doc;
    std::ifstream str(_dataDir / "controls.json");
    str >> doc;
    _controls.initConfig(doc,
                         {
                          {"yaw", _yaw},
                          {"roll", _roll},
                          {"pitch", _pitch},
                          {"throttle", _throttle},
                         });
  }

  {
    BOOST_LOG_TRIVIAL(info) << "Register callbacks";
    _physics.onTransform().connect
      ([this](engine::EntityId entityId, const glm::mat4 & transform)
       {
         if(entityId == _selfEntityId)
         {
           _graphics.setView(transform);
         }
         else
         {
           _graphics.setEntityTransform(entityId, transform);
         }
       });

    _controls.onAxis().connect
      ([this](engine::Controls::BindingId bindingId, int value)
       {
         if(bindingId == _pitch)
           _physics.updatePitchAxis(_selfEntityId,
                                    std::clamp(-value / 32767.0f, -1.0f, 1.0f));
         else if(bindingId == _roll)
           _physics.updateRollAxis(_selfEntityId,
                                   std::clamp(value / 32767.0f, -1.0f, 1.0f));
         else if(bindingId == _yaw)
           _physics.updateYawAxis(_selfEntityId,
                                   std::clamp(-value / 32767.0f, -1.0f, 1.0f));
         else if(bindingId == _throttle)
           _physics.updateThrottle(_selfEntityId,
                                   std::clamp(1 - (value + 32767) / 65535.0f, 0.0f, 1.0f));
       });
  }

  {
    BOOST_LOG_TRIVIAL(info) << "Register entities";
    Json::Value doc;
    std::ifstream str(_dataDir / "archetypes.json");
    str >> doc;
    _entityLibrary.registerArchetypes(doc);
  }
}

void space::World::initWorld()
{
  BOOST_LOG_TRIVIAL(info) << "Create world";

  _selfEntityId = _entityLibrary.createEntity("self");

  for(int index = 0; index < 1000; ++index)
  {
    _entityLibrary.createEntity("asteroid");
  }
}
