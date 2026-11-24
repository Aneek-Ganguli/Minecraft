//
// Created by Reall on 23-Nov-26.
//

#ifndef MINECRAFT_CHUNK_H
#define MINECRAFT_CHUNK_H

#include <Application.hpp>

#include "Cube.h"

constexpr int CHUNK_HEIGHT = 8;
constexpr int CHUNK_WIDTH = 8;
constexpr int CHUNK_DEPTH = 8;
inline Texture texture;

class Chunk {
    Application* app;
    Cube* cube[CHUNK_HEIGHT*CHUNK_HEIGHT * CHUNK_DEPTH];
public:
    Chunk(AG_EngineV2::Application* app);
    Chunk()=default;
    void draw(glm::mat4 projection);
    void destroy();
};


#endif //MINECRAFT_CHUNK_H