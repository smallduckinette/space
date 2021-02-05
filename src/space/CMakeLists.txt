add_executable(
  space
  space.cpp
  world.cpp)

target_link_libraries(
  space
  PRIVATE
  engine
  Boost::program_options
  Boost::log)
