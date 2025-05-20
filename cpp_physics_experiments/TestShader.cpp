#include "TestShader.h"

#include <fstream>
#include <sstream>

void TestShader::compile(const std::string& vertexPath, const std::string& fragmentPath) {
    // 1. Load shader source from file
    std::ifstream vertexFile(vertexPath);
    std::ifstream fragmentFile(fragmentPath);
    std::stringstream vertexBuffer, fragmentBuffer;

    if (!vertexFile || !fragmentFile) {
        std::cerr << "Failed to open shader files!" << std::endl;
        return;
    }

    vertexBuffer << vertexFile.rdbuf();
    fragmentBuffer << fragmentFile.rdbuf();

    std::string vertexSource = vertexBuffer.str();
    std::string fragmentSource = fragmentBuffer.str();

    // 2. Compile both shaders
    GLuint vertexShader = compileShader(vertexSource, GL_VERTEX_SHADER);
    GLuint fragmentShader = compileShader(fragmentSource, GL_FRAGMENT_SHADER);

    // 3. Link into shader program
    _programID = glCreateProgram();
    glAttachShader(_programID, vertexShader);
    glAttachShader(_programID, fragmentShader);
    glLinkProgram(_programID);

    // 4. Check for link errors
    GLint success;
    glGetProgramiv(_programID, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(_programID, 512, nullptr, infoLog);
        std::cerr << "Shader Program Linking Failed:\n" << infoLog << std::endl;
    }

    // 5. Cleanup
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

GLuint TestShader::compileShader(const std::string& source, GLenum type) {
    GLuint shaderID = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shaderID, 1, &src, nullptr);
    glCompileShader(shaderID);

    // Error checking
    GLint success;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
        std::cerr << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment")
            << " Shader Compilation Failed:\n" << infoLog << std::endl;
    }

    return shaderID;
}

void TestShader::use() {
    glUseProgram(_programID);
}