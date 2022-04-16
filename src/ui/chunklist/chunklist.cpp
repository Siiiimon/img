#include "chunklist.h"

void ShowChunkList(std::vector<Chunk*> &chunks, int totalChunksAmount,
                   std::function<void(int)>const& inspector,
                   std::function<void(unsigned long, unsigned long)>const& hexviewer) {
    ImGui::SetNextWindowSize(ImVec2(500, 150), ImGuiCond_Once);
    ImGui::Begin("Chunk List");
    
    if (chunks.empty()) {
        ImVec2 window_size = ImGui::GetWindowSize();
        ImVec2 msg_size = ImGui::CalcTextSize("No chunks available.");
        ImGui::Dummy(ImVec2(0.0f, window_size.y * 0.5f - msg_size.y * 2.0f));
        ImGui::Dummy(ImVec2(0.0f, 0.0f)); // empty dummy to make SameLine() work
        ImGui::SameLine(window_size.x * 0.5f - msg_size.x * 0.5f);
        ImGui::TextDisabled("No chunks available.");
    } else {
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar;
        ImGui::BeginChild("Chunklist Listchild", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y - 25), false, window_flags);
        ImGui::Columns(4);
        ImGui::Separator();
        ImGui::Text("Type"); ImGui::NextColumn();
        ImGui::Text("Length"); ImGui::NextColumn();
        ImGui::Text("CRC check"); ImGui::NextColumn();
        ImGui::Text("Ancillary field"); ImGui::NextColumn();
        ImGui::Separator();

        for (int i = 0; i < chunks.size(); i++) {
            ImGui::PushStyleColor(ImGuiCol_HeaderHovered, (ImVec4) ImColor(0, 0, 0, 20));
            ImGui::PushStyleColor(ImGuiCol_HeaderActive, (ImVec4) ImColor(0, 0, 0, 80));
            ImGui::Selectable(chunks[i]->Type().c_str(), false, ImGuiSelectableFlags_SpanAllColumns);
            ImGui::PopStyleColor(2);
            if (ImGui::IsItemHovered()) {
                hexviewer(chunks[i]->OffsetInFile(), chunks[i]->OffsetInFile() + chunks[i]->Length());
                if (ImGui::IsMouseDoubleClicked(0))
                    inspector(i);
            }
            ImGui::NextColumn();
            
            ImGui::Text("%d bytes", chunks[i]->Length()); ImGui::NextColumn();
            
            if (chunks[i]->IsCrcValid()) {
                ImGui::PushStyleColor(ImGuiCol_Text, (ImVec4) ImColor(0.0f, 255.0f, 0.0f));
                ImGui::Text("Valid");
            } else {
                ImGui::PushStyleColor(ImGuiCol_Text, (ImVec4) ImColor(255.0f, 0.0f, 0.0f));
                ImGui::Text("Invalid");
            }
            ImGui::PopStyleColor(1);
            ImGui::NextColumn();
            
            if (chunks[i]->IsCritical()) ImGui::Text("Critical");
            else ImGui::Text("Ancillary");
        }
        ImGui::Columns(1); ImGui::Separator();
        ImGui::EndChild();
        ImGui::Separator();
        ImGui::Text("Available chunks: %lu", chunks.size()); ImGui::SameLine(0, 20);
        ImGui::Text("Unrecognized chunks: %lu", totalChunksAmount - chunks.size());
    }
    
    ImGui::End();
}
