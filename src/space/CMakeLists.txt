add_executable(
  space
  physics.cpp
  space.cpp
  world.cpp)

target_link_libraries(
  space
  PRIVATE
  engine
  Boost::program_options
  Boost::log)
