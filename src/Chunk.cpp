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

        if (cube[i]->enable && i >  8) {
            int above = (i / CHUNK_HEIGHT) % CHUNK_WIDTH;
            int right = i / (CHUNK_HEIGHT * CHUNK_WIDTH);
            int front = i % CHUNK_DEPTH;
            if (above>0 && right > 0 && front > 0 ) {
                if (cube[above]->enable && cube[right]->enable && cube[front]->enable && above < CHUNK_WIDTH - 1 && right < CHUNK_HEIGHT - 1 && front < CHUNK_DEPTH - 1 ) {
                    cube[i]->enable = false;
                }
            }
        }



        // else {
            // cube[i]->enable = true;

        cube[i]->draw(projection);
        // if (cube[i)
    }
}

void Chunk::destroy() {
    texture.destroy(app->device.device);
    for (int i = 0; i < CHUNK_HEIGHT*CHUNK_WIDTH*CHUNK_DEPTH; i++) {
        cube[i]->destroy();
        delete cube[i];
    }
}
