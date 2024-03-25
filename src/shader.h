//
// Created by Neo on 25.03.2024.
//

#ifndef GAME_SHADER_H
#define GAME_SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "FilePWD.h"
#include <iostream>
#include <string>
#include <filesystem>

class Shader {
public:
    GLuint ID;

    Shader(
            const std::filesystem::path& vertexPath,
            const std::filesystem::path& fragmentPath
            );

    void use() const;

    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;

    ~Shader();

private:
    [[nodiscard]] static GLuint init() ;
    GLuint createShader(GLenum type, const char* source);
    void link_shader(GLuint shaderID) const;
    void link_program() const;
    void compile(GLuint shaderID) const;
};

#endif //GAME_SHADER_H
