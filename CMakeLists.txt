cmake_minimum_required (VERSION 3.16.3)
project (Space)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_compile_options(-Wall -Wextra -pedantic -Werror -O3)

include(CTest)

find_package(Boost 1.71 COMPONENTS system unit_test_framework log program_options)
find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
pkg_check_modules(JSONCPP REQUIRED IMPORTED_TARGET jsoncpp)
pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET sdl2)
pkg_check_modules(SDL2IMAGE REQUIRED IMPORTED_TARGET SDL2_image)
pkg_check_modules(SDL2TTF REQUIRED IMPORTED_TARGET SDL2_ttf)

find_package(Doxygen)
doxygen_add_docs(
  doxygen
  ${CMAKE_SOURCE_DIR}/src)

find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)

add_subdirectory(src)
