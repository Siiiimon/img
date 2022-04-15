#include "chunk.h"

Chunk::Chunk(uint32_t length, char type[4], std::vector<char> data, unsigned int crc) {
    m_length = length;
    memcpy(m_type, type, 4);
    for (char c : m_type) {
        m_type_string.push_back(c);
    }
    m_data = std::move(data);
    m_crc = crc;
}

int Chunk::Length() {
    return m_length;
}

std::string Chunk::Type() {
    return m_type_string;
}

bool Chunk::IsCritical() {
    return m_type[0] < 'a';
}

bool Chunk::IsCrcValid() {
    // TODO
    return true;
}

void Chunk::ShowInspectorContent() {
    static const char* msg = "Cannot inspect this chunk.";
    ImVec2 window_size = ImGui::GetWindowSize();
    ImVec2 msg_size = ImGui::CalcTextSize(msg);
    ImGui::Dummy(ImVec2(0.0f, window_size.y * 0.5f - msg_size.y * 2.0f));
    ImGui::Dummy(ImVec2(0.0f, 0.0f)); // empty dummy to make SameLine() work
    ImGui::SameLine(window_size.x * 0.5f - msg_size.x * 0.5f);
    ImGui::TextDisabled("%s", msg);
}
