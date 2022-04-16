#ifndef IMG_HEXVIEW_H
#define IMG_HEXVIEW_H

#include <fstream>
#include <iostream>
#include <fmt/core.h>

#include <imgui.h>

#include "../dearies/dearies.h"
#include "../../util.h"

void ShowHexView(const char *path, bool* p_open, unsigned long highlightFrom = -1, unsigned long highlightTo = -1);

#endif //IMG_HEXVIEW_H
