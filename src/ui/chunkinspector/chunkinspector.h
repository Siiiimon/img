#ifndef IMG_CHUNKINSPECTOR_H
#define IMG_CHUNKINSPECTOR_H

#include <iostream>
#include <vector>

#include <imgui.h>

#include "../../png/chunks/chunk.h"
#include "../../png/chunks/ihdr.h"

void ShowChunkInspector(std::vector<Chunk*> chunks, int index = 0);

#endif /* IMG_CHUNKINSPECTOR_H */
