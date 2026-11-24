//
// Created by Reall on 22-Nov-26.
//

#include "Game.h"

#include "ext/matrix_transform.hpp"

Game::Game():app("Minecraft", 800, 600, false) {

    chunk = Chunk(&this->app);

    camera = Camera(&this->app);

    lastTime = glfwGetTime();

    runGame();
}

void Game::runGame() {
    while (app.isWindowOpen()) {
        currentTime = glfwGetTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        app.startFrame();

        camera.update(deltaTime);

        chunk.draw(camera.getProjection());

        app.endFrame();
    }
}

Game::~Game() {
    app.waitIdle();

    chunk.destroy();
    // cube.destroy();
    app.destroy();
}