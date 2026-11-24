//
// Created by Reall on 22-Nov-26.
//

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include "Cube.h"

#include <ext/matrix_clip_space.hpp>
#include <ext/matrix_transform.hpp>


// Cube::Cube(Application* app, Texture texture, float x, float y, float z):
//     imageIndexUBO(app->device.device, app->physicalDevice.physicalDevice, sizeof(uint32_t), &index, 0, 0, 1, vk::DescriptorType::eUniformBuffer),
//     mvpUBO(app->device.device, app->physicalDevice.physicalDevice, sizeof(UBO), &mvp, 0, 0, 0, vk::DescriptorType::eUniformBuffer),
//     vertexData(loadModel("cube.obj",indices)),
//     cubeEntity(app, vertexData, indices, index, true, texture, imageIndexUBO, mvpUBO)
//
// {
//     float fov = glm::radians(45.0f);
//     float aspect = static_cast<float>(app->window.width) / static_cast<float>(app->window.height);
//     float nearPlane = 0.1f;
//     float farPlane = 100.0f;
//
//     mvp.projection = glm::perspective(fov, aspect, nearPlane, farPlane);
//
//
//     mvp.projection[1][1] *= -1.0f;
//
//
//     glm::vec3 cameraPos    = glm::vec3(0.0f, 0.0f, 2.0f);
//     glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
//     glm::vec3 upVector     = glm::vec3(0.0f, 1.0f, 0.0f);
//
//     mvp.view = glm::lookAt(cameraPos, cameraTarget, upVector);
//
//     mvp.model = glm::translate(glm::mat4(1.f), glm::vec3(y, x, z));
//     mvpUBO.updateData(&mvp);
//
//
// }

Cube::Cube(Application *app,float x, float y, float z)
    :_app(app)
{
    if (!done) {
        done = true;
        vertices = loadModel("cube.glb", indices);
        vertexBuffer = VertexBuffer(app->device.device, app->physicalDevice.physicalDevice, app->commandPool[0].commandPool, &app->queue, vertices);
        indexBuffer = IndexBuffer(app->device.device, app->physicalDevice.physicalDevice, app->commandPool[0].commandPool, &app->queue, indices);
        dirtTexture = std::make_unique<Texture>(app->device.device, &app->queue, app->physicalDevice.physicalDevice, "dirt.jpg", false);
        imageIndexUBO = std::make_unique<UniformBuffer>(app->device.device, app->physicalDevice.physicalDevice, sizeof(uint32_t), &imageIndex, 0, 0, 1, vk::DescriptorType::eUniformBuffer);
    }

    float fov = glm::radians(45.0f);
    float aspect = static_cast<float>(app->window.width) / static_cast<float>(app->window.height);
    float nearPlane = 0.1f;
    float farPlane = 100.0f;

    mvp.projection = glm::perspective(fov, aspect, nearPlane, farPlane);


    mvp.projection[1][1] *= -1.0f;


    glm::vec3 cameraPos    = glm::vec3(0.0f, 0.0f, 2.0f);
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 upVector     = glm::vec3(0.0f, 1.0f, 0.0f);

    mvp.view = glm::lookAt(cameraPos, cameraTarget, upVector);

    mvp.model = glm::translate(glm::mat4(1.f), glm::vec3(x, y, z));

    mvp.lightPosition = glm::vec3(x,y,z);
    mvpUBO = std::make_unique<UniformBuffer>(app->device.device, app->physicalDevice.physicalDevice, sizeof(UBO), &mvp, 0, 0, 0, vk::DescriptorType::eUniformBuffer);
    // mvpUBO->updateData(&mvp);

}


void Cube::destroy() {
    if (!destroyDone) {
        vertexBuffer.destroy(_app->device.device);
        indexBuffer.destroy(_app->device.device);
        imageIndexUBO->destroy(_app->device.device);
        dirtTexture->destroy(_app->device.device);
        dirtTexture.reset();
        imageIndexUBO.reset();
        destroyDone = true;
    }
    mvpUBO->destroy(_app->device.device);
    mvpUBO.reset();
}

void Cube::draw(glm::mat4 view) {
    mvp.view = view;
    mvpUBO->updateData(&mvp);
    _app->bindPipeline(true);
    _app->draw(&vertexBuffer, &indexBuffer, indices.size(), {mvpUBO->descriptorWrite, imageIndexUBO->descriptorWrite}, true);
    dirtTexture->update(imageIndex, _app->bindlessTextures.descriptorSet,_app->device.device);
}