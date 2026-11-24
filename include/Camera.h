//
// Created by Reall on 24-Nov-26.
//

#ifndef MINECRAFT_CAMERA_H
#define MINECRAFT_CAMERA_H
#include "Application.hpp"


class Camera {
    AG_EngineV2::Application* _app;
    glm::mat4 projection;
    float cameraYaw = -90.0f;
    float cameraPitch = 0.0f;
    glm::vec3 cameraPos;
    float lastFrameTime = static_cast<float>(glfwGetTime());
    double lastMouseX = 0.0, lastMouseY = 0.0;
    bool firstMouse = true;
public:
    Camera()=default;
    Camera(AG_EngineV2::Application* app);
    glm::mat4 getProjection(){return projection;}
    void update(float deltaTime);
};


#endif //MINECRAFT_CAMERA_H