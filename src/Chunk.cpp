//
// Created by Reall on 23-Nov-26.
//

#include "Chunk.h"

#include "ext/matrix_transform.hpp"

Chunk::Chunk(AG_EngineV2::Application *app) {
    texture = Texture(app->device.device, &app->queue,app->physicalDevice.physicalDevice, "dirt.jpg", false);
    for (float i = 0; i < CHUNK_SIZE; i++) {
        cube[(int)i] = new Cube(app,  i+1, i,i);
    }
}

void Chunk::draw() {
    for (int i = 0; i < CHUNK_SIZE; i++) {
        cube[i]->draw(

                glm::lookAt(
                        glm::vec3(0.0f, 10.f, 10.f),
                        glm::vec3(0.0f, 0.0f, -7.f),
                        glm::vec3(0.f, 1.f, 0.f)
                )
        );
    }
}

void Chunk::destroy() {
    for (int i = 0; i < CHUNK_SIZE; i++) {
        cube[i]->destroy();
        delete cube[i];
    }
}
