#ifndef IMG_DEARIES_H
#define IMG_DEARIES_H
// a place for custom-ish imgui widgets to live

#include <imgui.h>
#include "../../util.h"

void TextHighlightHover(const char *text, ImU32 col);
void TextHighlightIfInRect(const char *text, ImU32 col, Rect selection);
void TextHighlight(const char *text, ImU32 col);

#endif //IMG_DEARIES_H
