#include <iostream>
#include <filesystem>
#include <fstream>

#include <boost/log/trivial.hpp>
#include <boost/program_options.hpp>
#include <SDL2/SDL.h>

#include "engine/core/app.h"


namespace po = boost::program_options;


int main(int argc, char ** argv)
{
  try
  {
    std::filesystem::path config;

    engine::App app;

    app.add_options()
      ("config,c", po::value<std::filesystem::path>(&config), "Control configuration file");

    if(app.run(argc, argv))
    {
      BOOST_LOG_TRIVIAL(info) << "Init...";
    }
    return 0;
  }
  catch(const std::exception & e)
  {
    SDL_Quit();
    BOOST_LOG_TRIVIAL(error) << e.what();
    return -1;
  }
}
