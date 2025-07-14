# Ensure subprojects requiring older CMake version still work
set(CMAKE_POLICY_VERSION_MINIMUM 3.5 CACHE STRING "" FORCE)

cmake_minimum_required(VERSION 3.16)
project(BorgoHub LANGUAGES CXX)

# C++ settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Tell CMake where to find the SFML 2.5 config (Homebrew)
set(SFML_DIR "/opt/homebrew/opt/sfml@2/lib/cmake/SFML" CACHE PATH "Path to SFML 2.x CMake config")
find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system)

# Pull in ImGui & ImGui-SFML via FetchContent
include(FetchContent)

FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG        v1.89.8
)
FetchContent_Declare(
  imgui-sfml
  GIT_REPOSITORY https://github.com/eliasdaler/imgui-sfml.git
  GIT_TAG        v2.4
)

# Disable static SFML libs requirement in ImGui-SFML
set(IMGUI_SFML_USE_STATIC_LIB OFF CACHE BOOL "Use SFML dynamic libs" FORCE)

FetchContent_MakeAvailable(imgui imgui-sfml)

# Include paths for our engine & game code
target_include_directories(BorgoHub PUBLIC
  ${CMAKE_SOURCE_DIR}/Engine
  ${CMAKE_SOURCE_DIR}/games
)

# Gather engine & game sources
file(GLOB_RECURSE ENGINE_SOURCES
  ${CMAKE_SOURCE_DIR}/Engine/*.h
  ${CMAKE_SOURCE_DIR}/Engine/*.cpp
)
file(GLOB_RECURSE GAME_SOURCES
  ${CMAKE_SOURCE_DIR}/games/**/*.cpp
)

# Define the executable with main plus all sources
add_executable(BorgoHub
  src/main.cpp
  ${ENGINE_SOURCES}
  ${GAME_SOURCES}
)

# Link libraries
target_link_libraries(BorgoHub PRIVATE
  SFML::Graphics
  SFML::Window
  SFML::System
  imgui
  imgui-sfml
)
