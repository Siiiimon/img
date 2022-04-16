#ifndef IMG_IHDR_H
#define IMG_IHDR_H

#include "chunk.h"
#include "../../util.h"

#include <cstdio>
#include <stdexcept>
#include <vector>
#include <utility>

enum Malformation {
    Compression = (1u << 0),
    Filter = (1u << 1),
};

class Ihdr : public Chunk {
    unsigned int m_width; // TODO: cannot be zero
    unsigned int m_height;
    unsigned int m_bit_depth;
    unsigned int m_color_type;
    // verify compression bit (0)
    // verify filter method bit (0)
public:
    Ihdr(uint32_t length, char type[4], std::vector<char> data, unsigned int crc, unsigned long offsetInFile);
    int Width();
    int Height();
    int BitDepth(); // could define enums for these
    int ColorType();
    bool IsInterlaced();
    unsigned int IsCompressionOrFilterBitMalformed();

    void ShowInspectorContent() override;
};

#endif /* IMG_IHDR_H */
