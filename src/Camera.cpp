//
// Created by Reall on 24-Nov-26.
//

#include "Camera.h"

#include "ext/matrix_transform.hpp"

Camera::Camera(AG_EngineV2::Application *app)
:_app(app)
{
    cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    cameraYaw = -90.0f;
    cameraPitch = 0.0f;
    lastFrameTime = static_cast<float>(glfwGetTime());
    lastMouseX = 0.0, lastMouseY = 0.0;
    firstMouse = true;
}

void Camera::update(float deltaTime) {

    glm::vec3 moveInput(0.0f);
    if (glfwGetKey(_app->window.window, GLFW_KEY_W) == GLFW_PRESS) moveInput.z += 1.0f;
    if (glfwGetKey(_app->window.window, GLFW_KEY_S) == GLFW_PRESS) moveInput.z -= 1.0f;
    if (glfwGetKey(_app->window.window, GLFW_KEY_D) == GLFW_PRESS) moveInput.x += 1.0f;
    if (glfwGetKey(_app->window.window, GLFW_KEY_A) == GLFW_PRESS) moveInput.x -= 1.0f;
    if (glfwGetKey(_app->window.window, GLFW_KEY_SPACE) == GLFW_PRESS) moveInput.y += 1.0f;
    if (glfwGetKey(_app->window.window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) moveInput.y -= 1.0f;

    // Gather mouse input
    double currentMouseX, currentMouseY;
    glfwGetCursorPos(_app->window.window, &currentMouseX, &currentMouseY);

    if (firstMouse) {
        lastMouseX = currentMouseX;
        lastMouseY = currentMouseY;
        firstMouse = false;
    }

    float mouseDeltaX = static_cast<float>(currentMouseX - lastMouseX);
    float mouseDeltaY = static_cast<float>(currentMouseY - lastMouseY);
    lastMouseX = currentMouseX;
    lastMouseY = currentMouseY;

    int width, height;
    glfwGetFramebufferSize(_app->window.window, &width, &height);
    float aspectRatio = static_cast<float>(width) / static_cast<float>(height);

    constexpr float sensitivity = 4.f;
    cameraYaw   += mouseDeltaX * sensitivity;
    cameraPitch -= mouseDeltaY * sensitivity;
    cameraPitch = glm::clamp(cameraPitch, -89.0f, 89.0f);

    // 2. Direction vectors
    glm::vec3 front;
    front.x = cos(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
    front.y = sin(glm::radians(cameraPitch));
    front.z = sin(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
    front = glm::normalize(front);
    //
    constexpr glm::vec3 worldUp(0.0f, 1.0f, 0.0f);
    glm::vec3 right = glm::normalize(glm::cross(front, worldUp));
    glm::vec3 up    = glm::normalize(glm::cross(right, front));

    // 3. Position update
    constexpr float speed = 5.0f;
    cameraPos += front * moveInput.z * speed * deltaTime;
    cameraPos += right * moveInput.x * speed * deltaTime;
    cameraPos += worldUp * moveInput.y * speed * deltaTime;

    projection = lookAt(cameraPos, cameraPos + front, up);
}

