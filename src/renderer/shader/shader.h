#ifndef IMG_SHADER_H
#define IMG_SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <stdexcept>
#include <fmt/core.h>

class Shader
{
public:
    unsigned int ID;
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();
    void Use();
    void Set(const std::string &name, bool value) const;
    void Set(const std::string &name, int value) const;
    void Set(const std::string &name, float value) const;

private:
    static void checkCompileErrors(unsigned int shader, const std::string& type);
};
#endif //IMG_SHADER_H
