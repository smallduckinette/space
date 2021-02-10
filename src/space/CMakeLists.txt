add_executable(
  space
  debrisentity.cpp
  physics.cpp
  shipentity.cpp
  space.cpp
  world.cpp)

target_link_libraries(
  space
  PRIVATE
  engine
  Boost::program_options
  Boost::log)
