cmake_minimum_required(VERSION 3.28)
project(dondolagame_recreation)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.0
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

# Define the source and destination for your assets
set(ASSETS_SOURCE_DIR "${CMAKE_SOURCE_DIR}/assets")
set(ASSETS_OUTPUT_DIR "${CMAKE_BINARY_DIR}/assets")

add_executable(dondolagame_recreation main.cpp
        src/GameManager.cpp
        src/GameManager.h
        src/Player.cpp
        src/Player.h
        src/Enemy.cpp
        src/Enemy.h
        src/EnemyManager.h
        src/EnemyManager.cpp
        src/prg.h
        src/MyDebugger.h
        src/jsonReader.cpp
        src/jsonReader.h)
target_link_libraries(dondolagame_recreation PRIVATE SFML::Graphics)

# Create a custom command to copy the assets
add_custom_command(
        TARGET dondolagame_recreation POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${ASSETS_SOURCE_DIR} ${ASSETS_OUTPUT_DIR}
)
