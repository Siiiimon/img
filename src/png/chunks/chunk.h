#ifndef IMG_CHUNK_H
#define IMG_CHUNK_H

#include <cstdint>
#include <string>
#include <cstdlib>
#include <vector>
#include <utility>

#include <imgui.h>

class Chunk {
protected:
    uint32_t m_length;
    char m_type[4]{}; // clang complains otherwise
    std::string m_type_string;
    std::vector<char> m_data;
    unsigned int m_crc;
    unsigned long m_offsetInFile;
//    bool m_is_ok;
public:
    Chunk(uint32_t length, char type[4], std::vector<char> data, unsigned int crc, unsigned long offsetInFile);
    virtual ~Chunk() = default;
    int Length();
    std::string Type();
    bool IsCritical();
    bool IsCrcValid();
    unsigned long OffsetInFile();
    // TODO: function to check if chunk is valid. if not get error.
//    Okable<std::string> Ok();

    virtual void ShowInspectorContent();
};

#endif /* IMG_CHUNK_H */
