//
// Created by Reall on 22-Nov-26.
//

#ifndef MINECRAFT_CUBE_H
#define MINECRAFT_CUBE_H
#include <GLFW/glfw3.h>
#include <memory>
#include <Entity.hpp>


inline std::unique_ptr<Texture> dirtTexture;
inline VertexBuffer vertexBuffer;
inline IndexBuffer indexBuffer;
inline uint32_t imageIndex = 0;
inline std::unique_ptr<UniformBuffer> imageIndexUBO;
inline std::vector<VertexData> vertices;
inline std::vector<uint16_t> indices;
inline bool done = false;
inline bool destroyDone = false;

class Cube {
    Application* _app;
    // uint32_t index = 0;
    // UBO mvp;
    // UniformBuffer mvpUBO;
    // UniformBuffer imageIndexUBO;
    // std::vector<std::uint16_t> indices;
    // std::vector<VertexData>  vertexData;
    // Entity cubeEntity;

    std::unique_ptr<UniformBuffer> mvpUBO;
public:
    Cube(Application* app, float x, float y, float z);
    Cube()=default;
    void destroy();
    void draw(glm::mat4 view);
    bool enable = true;
    UBO mvp;
};


#endif //MINECRAFT_PLAYER_H