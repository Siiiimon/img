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

    float m_deltaTime = 0.0f;
    unsigned long long m_ticks = 0;
    float m_deltas[100] = {0.0f};
    float m_lastFrame = 0.0f;

public:
    Renderer(int width, int height);
    ~Renderer();
    int getWidth() const;
    int getHeight() const;
    GLFWwindow *getWindow() const;
    float getDeltaTime() const;
    float getAverageFps() const;
    void render(const std::function<void()>& update);
    void SetVsync(bool enabled);

private:
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void processInput(GLFWwindow* window);
};

#endif //IMG_RENDERER_H
