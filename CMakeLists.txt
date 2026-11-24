cmake_minimum_required(VERSION 4.0)
project(Minecraft)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib/AG_Engine EXCLUDE_FROM_ALL)

add_executable(Minecraft src/main.cpp
        src/Game.cpp
        src/Cube.cpp
        src/Chunk.cpp
        include/Game.h
        include/Cube.h
        include/Chunk.h
)

target_include_directories(Minecraft
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib/AG_Engine/lib/glfw/include>
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/lib
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/AG_Engine/lib/glm/glm
        PUBLIC
        "C:/Program Files/Assimp/include"
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/AG_Engine/include
        PUBLIC
)


target_link_libraries(Minecraft VulkanProjectV2)
link_libraries()