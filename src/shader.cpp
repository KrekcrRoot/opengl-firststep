//
// Created by Neo on 25.03.2024.
//

#include "shader.h"

/*
 *  CONSTRUCTOR
 *
 * */

Shader::Shader(
        const std::filesystem::path &vertexPath,
        const std::filesystem::path &fragmentPath
        ) {

    this->ID = Shader::init();

    std::string source = FilePWD::readFile(vertexPath);
    this->createShader(GL_VERTEX_SHADER, source.c_str());

    source = FilePWD::readFile(fragmentPath);
    this->createShader(GL_FRAGMENT_SHADER, source.c_str());

    this->link_program();
}

/*
 *  PRIVATE METHODS
 *
 * */

GLuint Shader::init() {
    GLuint program = glCreateProgram();
    return program;
}

GLuint Shader::createShader(GLenum type, const char* source) {

    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);

    this->compile(shader);
    this->link_shader(shader);

    return shader;

}

void Shader::compile(GLuint shaderID) const {

    int success;
    glCompileShader(shaderID);
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

    if(!success) {
        char log[512];
        glGetShaderInfoLog(shaderID, 512, nullptr, log);
        std::cerr << "ERROR::SHADER::COMPILE_STATUS::ID(" << shaderID << ")\n"
                  << "SHADER::PROGRAM::ID(" << this->ID << ")\n" << log << std::endl;
        exit(EXIT_FAILURE);
    }

}

void Shader::link_shader(GLuint shaderID) const {

    int success;
    glAttachShader(this->ID, shaderID);
    glGetProgramiv(this->ID, GL_ATTACHED_SHADERS, &success);

    if(!success) {
        char log[512];
        glGetProgramInfoLog(this->ID, 512, nullptr, log);
        std::cerr << "ERROR::PROGRAM::ATTACH_SHADER::ID(" << shaderID << ")\n"
                  << "SHADER::PROGRAM::ID(" << this->ID << ")\n" << log << std::endl;
        exit(EXIT_FAILURE);
    }

    glDeleteShader(shaderID);

}

void Shader::link_program() const {

    int success;
    glLinkProgram(this->ID);

    glGetProgramiv(this->ID, GL_LINK_STATUS, &success);

    if (!success) {
        char log[512];
        glGetProgramInfoLog(this->ID, 512, nullptr, log);
        std::cerr << "ERROR::PROGRAM::LINK_STATUS\nPROGRAM::ID(" << this->ID << ")\n"
                  << log << std::endl;
        exit(EXIT_FAILURE);
    }

}


/*
 *  PUBLIC METHODS
 *
 * */

void Shader::use() const {
    glUseProgram(this->ID);
}

void Shader::setBool(const std::string &name, bool value) const {
    GLint location = glGetUniformLocation(this->ID, name.c_str());
    glUniform1i(location, (int) value);
}

void Shader::setInt(const std::string &name, int value) const {
    GLint location = glGetUniformLocation(this->ID, name.c_str());
    glUniform1i(location, value);
}

void Shader::setFloat(const std::string &name, float value) const {
    GLint location = glGetUniformLocation(this->ID, name.c_str());
    glUniform1f(location, value);
}

Shader::~Shader() {
    glDeleteProgram(this->ID);
}
