#include "app.h"

App::App() {
    m_renderer = new Renderer(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    m_showDemo = true;
    m_showInternals = true;
}

void App::update() {
    if (m_showInternals) {
        ImGui::Begin("Debug", &m_showInternals);
        ImGui::Text("Window dimensions: %d x %d", m_renderer->getWidth(), m_renderer->getHeight());
        ImGui::Text("Delta time: %f", m_renderer->getDeltaTime());
        ImGui::Text("GLFW window handle: %p", m_renderer->getWindow());
        ImGui::End();
    }

    if (m_showDemo)
        ImGui::ShowDemoWindow(&m_showDemo);
}

void App::run() {
    m_renderer->render([this] { update(); });
}

App::~App() {
    delete m_renderer;
}
