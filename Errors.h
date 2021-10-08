#ifndef ERRORS_H
#define ERRORS_H

#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <vector>

#include "glad.c"

#define ERRORS_H

namespace errors {
    void shaderCheck(const std::vector<unsigned>& shaderIDs) {
        int success;
        char infoLog[512];

        for (const auto& ID : shaderIDs) {
            glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(ID, 512, NULL, infoLog);
                std::cout << "Error::Shader::Compilation_Failed" << std::endl << infoLog << std::endl;
            }
        }
    }

    void programCheck(const std::vector<unsigned>& programs) {
        int success;
        char infoLog[512];

        for (const auto& program : programs) {
            glGetProgramiv(program, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(program, 512, NULL, infoLog);
                std::cout << "Error::Shader::Linking::Failed" << std::endl << infoLog << std::endl;
            }
        }
    }
}

#endif