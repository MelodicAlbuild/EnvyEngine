cmake_minimum_required(VERSION 3.22)
project(EnvyEngine)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} src/main.cpp
        src/Core/Game.cpp src/Render/Sprite.cpp
        src/Render/SpritePosition.cpp
        src/Render/EnvyRenderer.cpp
        src/Core/Events/EnvyEventManager.cpp
        src/Core/Events/EnvyEventListener.cpp
        src/Render/DirectionHelper.cpp
        src/Objects/Object.cpp)

# --- SDL2 SETUP ---
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
set(SDL2_PATH "vendor/SDL2/x86_64-w64-mingw32")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES})