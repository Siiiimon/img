#include "png.h"

Png::Png(Logger* logger): m_logger(logger) {}

void Png::Read(const char *path, bool throwOnError) {
    if(m_logger != nullptr) m_logger->Logf("Opening file %s\n", path);
    std::ifstream in(path, std::ios_base::in | std::ios_base::binary);
    if (!in || in.fail() || !in.is_open()) {
        err(fmt::format("Failed to open file: {}", path), throwOnError);
        return;
    }
    
    // check header
    char header[8];
    in.read((char *)&header, 8);
    if (!in || in.fail()) {
        err(fmt::format("Failed to read 'header' at {}", in.tellg()), throwOnError);
        return;
    }
    const unsigned char valid_header[8] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A}; // maybe define these values
    if (memcmp(header, valid_header, 8) != 0) {
        in.close();
        err("invalid PNG header", throwOnError);
        return;
    } else {
        if (m_logger != nullptr) m_logger->Logln("Header is valid");
    }

    m_totalChunks = 0;
    bool eof = false;
    while(!eof) {
        // TODO: generate warning if ihdr or iend are out of place
        // TODO: generate warning on missing idat chunk
        unsigned long currentOffset = in.tellg();
        char len_buf[4];
        in.read((char*)&len_buf, 4);
        if (!in || in.fail()) {
            err(fmt::format("Failed to read 'len' at {}", in.tellg()), throwOnError);
            return;
        }
        uint32_t len = deserialiseInt(len_buf, true);
        
        char type[4];
        in.read((char*)&type, 4);
        if (!in || in.fail()) {
            err(fmt::format("Failed to read 'type' at {}", in.tellg()), throwOnError);
            return;
        }

        // TODO: generate warning if 3rd letter is not uppercase
        
        char rawData[len];
        std::vector<char> data;
        if (len <= DEFAULT_MAX_CHUNK_READ_SIZE) {
//            data.reserve(len);
            in.read((char *) &rawData, len);
            for (int i = 0; i < len; ++i) {
                data.push_back(rawData[i * sizeof(char)]);
            }
            if (!in || in.fail()) {
                err(fmt::format("Failed to read 'data' at {}", in.tellg()), throwOnError);
                return;
            }
//            data.resize(in.gcount());
        } else {
            // TODO: stream instead
            in.ignore(len);
        }
        
        char crc_buf[4];
        in.read((char *)&crc_buf, 4);
        if (!in || in.fail()) {
            err(fmt::format("Failed to read 'crc' at {}", in.tellg()), throwOnError);
            return;
        }
        unsigned int crc = deserialiseInt(crc_buf, true);
        m_totalChunks++;
        currentOffset += 8ul; // add the remaining 8 bytes from the header

        if (strncmp(type, "IHDR", 4) == 0) m_chunks.push_back(new Ihdr(len, type, data, crc, currentOffset));
        if (strncmp(type, "IEND", 4) == 0) eof = true;
    }
    if (!in.eof()) {
        auto current = in.tellg();
        in.seekg(0, std::ios_base::end);
        long long missed = in.tellg() - current;
        if (m_logger != nullptr && missed > 0)
            m_logger->Logf("IEND encountered but we're not at EOF yet, missed %lld bytes\n", missed);
    }
    in.close();
    if (m_logger != nullptr) m_logger->Logln("Finished reading file");
}

int Png::GetTotalChunks() const {
    return m_totalChunks;
}

std::vector<Chunk*> &Png::GetChunks() { 
    return m_chunks;
}

Png::~Png() {
    for (Chunk* chunk : m_chunks) {
        delete chunk;
    }
}

void Png::err(const std::string& msg, bool throwOnError) {
    if (throwOnError) {
        throw std::runtime_error(msg);
    } else {
        if (m_logger != nullptr) m_logger->Logln(msg.c_str());
    }
}
