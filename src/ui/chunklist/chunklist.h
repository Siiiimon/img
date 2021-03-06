#ifndef IMG_CHUNKLIST_H
#define IMG_CHUNKLIST_H

#include <cstdio>
#include <vector>
#include <imgui.h>

#include "../../png/chunks/chunk.h"
#include "../chunkinspector/chunkinspector.h"

void ShowChunkList(std::vector<Chunk*> &chunks, int totalChunksAmount,
                   std::function<void(int)>const& inspector,
                   std::function<void(unsigned long, unsigned long)>const& hexviewer);

#endif /* IMG_CHUNKLIST_H */
