#include <iostream>
#include <filesystem>
#include <fstream>

#include <boost/log/trivial.hpp>
#include <boost/program_options.hpp>
#include <SDL2/SDL.h>

#include "engine/core/app.h"
#include "engine/core/clock.h"
#include "space/world.h"


namespace po = boost::program_options;


int main(int argc, char ** argv)
{
  try
  {
    std::filesystem::path dataDir;

    engine::App app;

    app.enableGraphics();

    app.add_options()
      ("data,d", po::value<std::filesystem::path>(&dataDir)->default_value("data"), "Data directory");

    if(app.run(argc, argv))
    {
      space::World world(app.clock(), app.resX(), app.resY(), dataDir);

      bool running = true;
      float t1 = app.clock()->getTimestamp();
      while(running)
      {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
          if(event.type == SDL_QUIT)
          {
            running = false;
          }
        }

        float t2 = app.clock()->getTimestamp();
        float d = t2 - t1;
        BOOST_LOG_TRIVIAL(debug) << 1 / d;
        t1 = t2;

        world.onFrame();
        SDL_GL_SwapWindow(app.window());
      }
    }

    SDL_Quit();
  }
  catch(const std::exception & e)
  {
    SDL_Quit();
    BOOST_LOG_TRIVIAL(error) << e.what();
    return -1;
  }
  return 0;
}
