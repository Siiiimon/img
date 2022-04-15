#include "app.h"

App::App() {
    m_showDemo = true;
    m_showInternals = true;
    m_vsync = true;
    m_renderer = new Renderer(DEFAULT_WIDTH, DEFAULT_HEIGHT);
}

void App::update() {
    if (m_showInternals) {
        ImGui::Begin("Debug", &m_showInternals);
        ImGui::Text("Window dimensions: %d x %d", m_renderer->getWidth(), m_renderer->getHeight());
        ImGui::Text("Delta Time: %f", m_renderer->getDeltaTime());
        ImGui::Text("Average fps: %.1f", m_renderer->getAverageFps());

        ImGui::AlignTextToFramePadding();
        ImGui::Text("Double buffering / Vsync:");
        ImGui::SameLine();
        if (ImGui::Button(m_vsync ? "on" : "off")) {
            m_vsync = !m_vsync;
            m_renderer->SetVsync(m_vsync);
        }
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
