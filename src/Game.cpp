//
// Created by Reall on 22-Nov-26.
//

#include "Game.h"

#include "ext/matrix_transform.hpp"

Game::Game():app("Minecraft", 800, 600, false) {

    cube = Cube(&this->app,0,0,-7);

    // chunk = Chunk(&this->app);

    runGame();
}

void Game::runGame() {
    while (app.isWindowOpen()) {
        app.startFrame();

        cube.draw(glm::lookAt(
                glm::vec3(0.0f, 10.f, 10.f),
                glm::vec3(0.0f, 0.0f, -7.f),
                glm::vec3(0.f, 1.f, 0.f)
        ));

        app.endFrame();
    }
}

Game::~Game() {
    app.waitIdle();

    // chunk.destroy();
    cube.destroy();
    app.destroy();
}