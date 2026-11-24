//
// Created by Reall on 23-Nov-26.
//

#ifndef MINECRAFT_CHUNK_H
#define MINECRAFT_CHUNK_H

#include <Application.hpp>

#include "Cube.h"

constexpr int CHUNK_SIZE = 32;
inline Texture texture;

class Chunk {
    Cube* cube[CHUNK_SIZE];
public:
    Chunk(AG_EngineV2::Application* app);
    Chunk()=default;
    void draw();
    void destroy();
};


#endif //MINECRAFT_CHUNK_H