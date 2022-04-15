#include "logger.h"

Logger::Logger() {
    Clear();
}

void Logger::ShowLog(bool *show_log) {
    ImGui::SetNextWindowSize(ImVec2(350, 200), ImGuiCond_FirstUseEver);
    ImGui::Begin("Logger", show_log);
    if (ImGui::Button("Clear")) {
        Clear();
    }
    ImGui::Separator();
    if (ImGui::BeginChild("log box", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar)) {
        ImGui::TextUnformatted(m_buf.begin(), m_buf.end());
    }
    ImGui::EndChild();
    ImGui::End();
}

void Logger::Clear() {
    m_buf.clear();
}

void Logger::Logf(const char *fmt, ...) {
    int old_size = m_buf.size();
    va_list args;
    va_start(args, fmt);
    m_buf.appendfv(fmt, args);
    va_end(args);
}

void Logger::Logln(const char* msg) {
    Logf("%s\n", msg);
}
