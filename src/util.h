#ifndef IMG_UTIL_H
#define IMG_UTIL_H

#include <cstdint>
#include <vector>

struct Rect {
    float x1;
    float y1;
    float x2;
    float y2;
};

uint32_t deserialiseInt(char buf[4], bool should_reverse);
uint32_t deserialiseInt(std::vector<char> buf, bool should_reverse);

#endif //IMG_UTIL_H
