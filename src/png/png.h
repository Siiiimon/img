#ifndef IMG_PNG_H
#define IMG_PNG_H

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstring>
#include <cstddef>
#include <cstdint>
#include <vector>

#include <fmt/core.h>

#include "../util.h"
#include "../ui/log/logger.h"
#include "chunks/chunk.h"
#include "chunks/ihdr.h"

#define DEFAULT_MAX_CHUNK_READ_SIZE 1024

class Png {
    std::vector<Chunk*> m_chunks;
    Logger* m_logger;
public:
    Png(Logger* logger);
    ~Png();
    void Read(const char *path, bool throwOnError);
    std::vector<Chunk*>& GetChunks();
private:
    void err(const std::string& msg, bool throwOnError);
};

#endif /* IMG_PNG_H */
