cmake_minimum_required(VERSION 3.28)
project(2DGameEngine LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(game
    src/main.cpp
    src/my_window/Graphics.cpp
    src/my_window/Window.cpp
    src/my_window/InputHandler.cpp
    src/Engine.cpp
    src/ecs/ECSDefinition.cpp
    src/ecs/ECSManager.cpp
    src/dsa/SparseSet.cpp
    src/dsa/IdGenerator.cpp
    src/ecs/ECS.cpp
    src/ecs/SystemDescriptor.cpp
    src/ecs/ComponentManager.cpp
    src/ecs/SystemManager.cpp
    src/dsa/Graph.cpp
    src/ecs/MessageHandler.cpp
    src/input/MovementController.cpp
    src/systems.cpp
    src/adapters.cpp
    src/dsa/Vector2.cpp
    src/ecs/ResourceManager.cpp
    src/ecs/Scheduler.cpp
    src/cttmp/cttmp.cpp
    src/physics/apis.hpp
    src/physics/PhysicWorld.cpp
)
target_include_directories(game PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_compile_features(game PRIVATE cxx_std_23)
target_link_libraries(game PRIVATE
    sfml-graphics
    sfml-audio
)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT game)
