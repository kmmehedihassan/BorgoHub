cmake_minimum_required(VERSION 3.16)
project(BorgoHub LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Find SFML (Homebrew installs to /opt/homebrew)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

include(FetchContent)
# ImGui core library
FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG v1.89.8
)
# ImGui-SFML binding
FetchContent_Declare(
  imgui-sfml
  GIT_REPOSITORY https://github.com/eliasdaler/imgui-sfml.git
  GIT_TAG v2.4
)
FetchContent_MakeAvailable(imgui imgui-sfml)

# expose our headers
target_include_directories(BorgoHub PRIVATE
  ${CMAKE_SOURCE_DIR}/Engine
  ${CMAKE_SOURCE_DIR}/games
)

# grab all .cpp in Engine/ and games/
file(GLOB_RECURSE GAME_SOURCES
    ${CMAKE_SOURCE_DIR}/Engine/*.cpp
    ${CMAKE_SOURCE_DIR}/games/*.cpp
)

# add them to the build
target_sources(BorgoHub PRIVATE ${GAME_SOURCES})
# Our executable
add_executable(BorgoHub
  src/main.cpp
  # (If you have engine sources, list them here or link as a library)
)

target_link_libraries(BorgoHub
  sfml-graphics
  sfml-window
  sfml-system
  imgui
  imgui-sfml
)
