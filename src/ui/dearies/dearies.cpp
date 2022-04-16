#include "dearies.h"

void TextHighlightHover(const char *text, ImU32 col) {
    ImVec2 txt_size = ImGui::CalcTextSize(text);
    ImVec2 cursor_pos = ImGui::GetCursorScreenPos();

    ImGui::Text("%s", text);
    if (ImGui::IsItemHovered()) {
        ImGui::GetWindowDrawList()->AddRectFilled(
                ImVec2(cursor_pos.x, cursor_pos.y),
                ImVec2(cursor_pos.x + txt_size.x, cursor_pos.y + txt_size.y),
                col
        );
    }
}

void TextHighlightIfInRect(const char *text, ImU32 col, Rect selection) {
    ImVec2 txt_size = ImGui::CalcTextSize(text);
    ImVec2 cursor_pos = ImGui::GetCursorScreenPos();
    Rect target = Rect{cursor_pos.x, cursor_pos.y,cursor_pos.x + txt_size.x, cursor_pos.y + txt_size.y};

    ImGui::Text("%s", text);

    // overlap test
    if (target.x1 > selection.x1 && target.x2 < selection.x2 &&
        target.y1 > selection.y1 && target.y2 < selection.y2) {
        ImGui::GetWindowDrawList()->AddRectFilled(
                ImVec2(cursor_pos.x, cursor_pos.y),
                ImVec2(cursor_pos.x + txt_size.x, cursor_pos.y + txt_size.y),
                col
        );
    }
}

void TextHighlight(const char *text, ImU32 col) {
    ImVec2 txt_size = ImGui::CalcTextSize(text);
    ImVec2 cursor_pos = ImGui::GetCursorScreenPos();

    ImGui::Text("%s", text);
    ImGui::GetWindowDrawList()->AddRectFilled(
            ImVec2(cursor_pos.x, cursor_pos.y),
            ImVec2(cursor_pos.x + txt_size.x, cursor_pos.y + txt_size.y),
            col
    );
}
