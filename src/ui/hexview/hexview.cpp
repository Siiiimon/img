#include "hexview.h"

void ShowHexView(const char *path, bool *p_open, unsigned long highlightFrom, unsigned long highlightTo) {
    // TODO: ascii row
    // TODO: different view-types at the bottom
    // TODO: make scroll stream the buffer
    //         integrate with currently open file
    const int buf_size = 1024;
    bool currentlyCrying = false;
    std::ifstream in(path, std::ios_base::in | std::ios_base::binary);
    if (!in || in.fail() || !in.is_open()) {
        std::cout << "Open Oopsie!" << std::endl;
        currentlyCrying = true;
    }
    unsigned char buf[buf_size] = {0};
    in.read((char *) &buf, buf_size * sizeof(char));
    if (!in || in.fail()) {
        std::cout << "Reading Oopsie!" << std::endl;
        currentlyCrying = true;
    }

    ImGui::SetNextWindowSize(ImVec2(400, 275), ImGuiCond_Once);
    ImGui::Begin("Hex View", p_open);

    ImGui::Text("Current File:   %s", path);
    ImGui::Separator();

    ImGui::BeginChild("HexView MainChild");
    ImColor highlightColor(255, 255, 255, 60);
    if (currentlyCrying) {
        ImVec2 window_size = ImGui::GetWindowSize();
        ImVec2 msg_size = ImGui::CalcTextSize("No Contents.");
        ImGui::Dummy(ImVec2(0.0f, window_size.y * 0.5f - msg_size.y * 2.0f));
        ImGui::Dummy(ImVec2(0.0f, 0.0f)); // empty dummy to make SameLine() work
        ImGui::SameLine(window_size.x * 0.5f - msg_size.x * 0.5f);
        ImGui::TextDisabled("No Contents.");
    } else {
        if (ImGui::BeginTable("HexView HexContents",
                              17,
                              ImGuiTableFlags_NoPadInnerX
                              | ImGuiTableFlags_NoPadOuterX)) {
            ImVec2 win_pos = ImGui::GetWindowPos();
            ImVec2 win_size = ImGui::GetWindowSize();
            // table setup
            // offset labels
            ImGui::TableSetupColumn("Row", ImGuiTableColumnFlags_WidthFixed, 50.0f);
            // round about way of drawing a separating line and i don't think i'm doing it right but whatever
            /*
             * maybe use this for the ascii seperator
            float cursorX = ImGui::GetCursorPosX();
            ImGui::GetWindowDrawList()->AddLine(
                    ImVec2(win_pos.x + cursorX + 50.0f * 0.75f, win_pos.y),
                    ImVec2(win_pos.x + cursorX + 50.0f * 0.75f, win_pos.y + win_size.y),
                    ImGui::GetColorU32(IM_COL32(255, 255, 255, 255)))
            */
            // first byte
            for (int i = 0; i < 7; i++) {
                ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 15.0f + (5.0f * (float) (i % 2)));
            }
            // last bit gets extra spacing to clear off the next byte
            ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 35.0f);
            // second byte
            for (int i = 0; i < 8; i++) {
                ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 15.0f + (5.0f * (float) (i % 2)));
            }


            for (int rowOffset = 0; rowOffset < buf_size; rowOffset += 16) {
                ImGui::TableNextRow();

                // print row offset label
                ImGui::TableSetColumnIndex(0);
                ImGui::Text("%04X:", rowOffset);

                // draw first byte
                for (unsigned long index = rowOffset; index < rowOffset + 8; index++) {
                    ImGui::PushItemWidth(-FLT_MIN);
                    ImGui::TableSetColumnIndex((int) index % 8 + 1);
                    if (index >= highlightFrom && index <= highlightTo)
                        TextHighlight(fmt::format("{:02X}", buf[index]).c_str(), highlightColor);
                    else
                        ImGui::Text("%02X", buf[index]);
                }

                // draw second byte
                for (unsigned long index = rowOffset + 8; index < rowOffset + 16; index++) {
                    ImGui::PushItemWidth(-FLT_MIN);
                    ImGui::TableSetColumnIndex((int) index % 8 + 9);
                    if (index >= highlightFrom && index <= highlightTo)
                        TextHighlight(fmt::format("{:02X}", buf[index]).c_str(), highlightColor);
                    else
                        ImGui::Text("%02X", buf[index]);
                }
            }
            ImGui::EndTable();
        }

//        for (int i = 0; i < 1024; i += 8) {
//            drawByte((unsigned char *) (buf + i));
//            ImGui::SameLine();
//            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f);
//            drawByte((unsigned char *) (buf + i + 8));
//        }
    }
    ImGui::EndChild();

    ImGui::End();
}
