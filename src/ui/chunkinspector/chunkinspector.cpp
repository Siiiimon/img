#include "chunkinspector.h"

void drawIHDR(Ihdr *chunk) {
    // TODO
}

void ShowChunkInspector(std::vector<Chunk*> chunks, int index) {
    ImGui::SetNextWindowSize(ImVec2(280, 375), ImGuiCond_Once);
    ImGui::Begin("Chunk Inspector");
    if (chunks.empty()) {
        // might be worth to wrap this "show emptiness" text in a helper function since it's pretty clunky and difficult to read
        static const char* msg = "No chunks available.";
        ImVec2 window_size = ImGui::GetWindowSize();
        ImVec2 msg_size = ImGui::CalcTextSize(msg);
        ImGui::Dummy(ImVec2(0.0f, window_size.y * 0.5f - msg_size.y * 2.0f));
        ImGui::Dummy(ImVec2(0.0f, 0.0f)); // empty dummy to make SameLine() work
        ImGui::SameLine(window_size.x * 0.5f - msg_size.x * 0.5f);
        ImGui::TextDisabled("%s", msg);
    } else {
        if (index < 0 && index >= chunks.size()) {
            std::cout << "[CHUNK INSPECTOR] given index is out of 'chunks' range: " << index << std::endl << "resetting index to 0" << std::endl;
            index = 0;
        }
        
        Chunk *current_chunk = chunks[index];
        const char* combo_current_chunk_name = current_chunk->Type().c_str();
        if (ImGui::BeginCombo("Chunks", combo_current_chunk_name)) {
            for (Chunk *chunk : chunks) {
                bool is_selected = chunk->Type().c_str() == combo_current_chunk_name;
                if (ImGui::Selectable(chunk->Type().c_str(), is_selected))
                    combo_current_chunk_name = chunk->Type().c_str();
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }

        current_chunk->ShowInspectorContent();
//        if (current_chunk->Type() == "IHDR") {
//            Ihdr* ihdr_chunk = dynamic_cast<Ihdr*>(current_chunk);
//            if (ihdr_chunk == nullptr) throw std::runtime_error("IHDR chunk is not instance of Ihdr. You may be entitled for compensation.");
//            ShowInspectorUIContent(ihdr_chunk);
//        } else {
//            ShowInspectorUIContent();
//        }
    }
    
    ImGui::End();
}
