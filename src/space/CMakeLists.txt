add_executable(
  space
  space.cpp)

target_link_libraries(
  space
  PRIVATE
  engine
  Boost::program_options
  Boost::log)
