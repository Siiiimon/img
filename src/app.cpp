#include "app.h"

App::App() {
    m_showList = false;
    m_showInspector = false;
    m_inspectorIndex = 0;
    m_showDemo = false;
    m_showInternals = false;
    m_vsync = true;
    m_showLogger = true;
    m_logger = new Logger();
    m_renderer = new Renderer(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    m_logger->Logln("App initialized");
    m_png = new Png(m_logger);
}

App::~App() {
    delete m_renderer;
}

void App::update() {
    drawMainMenu();

    if (m_showList)
        ShowChunkList(m_png->GetChunks(), [this](int i) {
            m_inspectorIndex = i;
            m_showInspector = true;
        });

    if (m_showInspector)
        ShowChunkInspector(m_png->GetChunks(), m_inspectorIndex);

    if (m_showInternals)
        showInternals(&m_showInternals);

    if (m_showLogger)
        m_logger->ShowLog(&m_showLogger);

    if (m_showDemo)
        ImGui::ShowDemoWindow(&m_showDemo);
}

void App::run() {
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

void App::drawMainMenu() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Open", "Ctrl+O")) {
                m_png->Read("assets/turtle.png", true);
                m_showList = true;
            }
            // TODO: option to try again without erroring out
            // TODO: open recent
            ImGui::Separator();
            if (ImGui::MenuItem("Exit", "ESC")) {
                // uhh...
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Windows")) {
            ImGui::MenuItem("Log", "", &m_showLogger);
            ImGui::MenuItem("Chunk List", "", &m_showList);
            ImGui::MenuItem("Chunk Inspector", "", &m_showInspector);
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}
