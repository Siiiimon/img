#include "app.h"

App::App() {
    m_showDemo = true;
    m_showInternals = true;
    m_vsync = true;
    m_showLogger = true;
    m_logger = new Logger();
    m_renderer = new Renderer(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    m_logger->Logln("App initialized");
}

void App::update() {
    if (m_showInternals)
        showInternals(&m_showInternals);

    if (m_showLogger)
        m_logger->ShowLog(&m_showLogger);

    if (m_showDemo)
        ImGui::ShowDemoWindow(&m_showDemo);
}

void App::run() {
    m_logger->Logln("Entering render-loop");
    m_renderer->render([this] { update(); });
}

void App::showInternals(bool *p_open) {
    ImGui::Begin("Debug", p_open);
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

App::~App() {
    delete m_renderer;
}
