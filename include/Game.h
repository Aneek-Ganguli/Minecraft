//
// Created by Reall on 22-Nov-26.
//

#ifndef MINECRAFT_GAME_H
#define MINECRAFT_GAME_H
#include <Application.hpp>

#include "Camera.h"
#include "Chunk.h"
#include "Cube.h"


class Game {
    AG_EngineV2::Application app;
    // Cube cube;
    Chunk chunk;
    Camera camera;
    float currentTime;
    float lastTime;
    void runGame();

public:
    Game();
    ~Game();
};


#endif //MINECRAFT_GAME_H