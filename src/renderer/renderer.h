#ifndef IMG_RENDERER_H
#define IMG_RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <stdexcept>

#include "shader/shader.h"

class Renderer {
    int m_width;
    int m_height;
    unsigned int m_vao{}, m_vbo{}, m_ebo{};
    Shader* m_shaders{};
    GLFWwindow* m_window{};

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

public:
    Renderer(int width, int height);
    ~Renderer();
    void render();

private:
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void processInput(GLFWwindow* window);
};

#endif //IMG_RENDERER_H
