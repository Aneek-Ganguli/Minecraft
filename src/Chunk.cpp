//
// Created by Reall on 23-Nov-26.
//

#include "Chunk.h"

#include <iostream>
#include <ostream>

#include "ext/matrix_transform.hpp"

Chunk::Chunk(AG_EngineV2::Application *app):app(app) {
    texture = Texture(app->device.device, &app->queue,app->physicalDevice.physicalDevice, "dirt.jpg", false);

    for (int i = 0; i < CHUNK_HEIGHT*CHUNK_WIDTH*CHUNK_DEPTH; i++) {
        cube[i] = new Cube(app, (i / (CHUNK_HEIGHT * CHUNK_WIDTH)) * 2.f, -((i / CHUNK_HEIGHT) % CHUNK_WIDTH) * 2.f, -(i % CHUNK_DEPTH) * 2.f);
    }
}

void Chunk::draw(glm::mat4 projection) {
    for (int i = 0; i < CHUNK_HEIGHT*CHUNK_DEPTH*CHUNK_DEPTH; i++) {
        cube[i]->draw(projection);
    }
}

void Chunk::destroy() {
    texture.destroy(app->device.device);
    for (int i = 0; i < CHUNK_HEIGHT*CHUNK_WIDTH*CHUNK_DEPTH; i++) {
        cube[i]->destroy();
        delete cube[i];
    }
}
