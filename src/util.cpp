#include "util.h"

uint32_t deserialiseInt(std::vector<char> buf, bool should_reverse) {
    if (should_reverse) std::reverse(buf.begin(), buf.end()); // reverse the array because of endianness
    uint32_t num = 0;
    std::memcpy(&num, buf.data(), sizeof(uint32_t));
    return num;
}

uint32_t deserialiseInt(char buf[4], bool should_reverse) {
    std::vector<char> temp(buf, buf + 4);
    return deserialiseInt(temp, should_reverse);
}