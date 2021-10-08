#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include "Errors.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class ShaderProgram {
public:
	ShaderProgram(const char* vertexPath, const char* fragmentPath);
	~ShaderProgram();

	void use(void) const;
	unsigned ID(void) const;
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;

private:
	unsigned programID;
};

ShaderProgram::ShaderProgram(const char* vertexPath, const char* fragmentPath) {
	std::ifstream vertexInput, fragmentInput;
	std::string vertexCode, fragmentCode;
	std::stringstream vertexShaderStream, fragmentShaderStream;

	vertexInput.exceptions (std::istream::failbit | std::ifstream::badbit);
	fragmentInput.exceptions (std::istream::failbit | std::ifstream::badbit);

	try {
		vertexInput.open(vertexPath);
		fragmentInput.open(fragmentPath);

		vertexShaderStream << vertexInput.rdbuf();
		fragmentShaderStream << fragmentInput.rdbuf();

		vertexInput.close();
		fragmentInput.close();

		vertexCode = vertexShaderStream.str();
		fragmentCode = fragmentShaderStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
	}

	const char* vertexShaderCode = vertexCode.c_str();
	const char* fragmentShaderCode = fragmentCode.c_str();

	unsigned vertex, fragment;

	GLint const vertexShaderSize = vertexCode.size();
	GLint const fragmentShaderSize = fragmentCode.size();

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexShaderCode, NULL);
	glCompileShader(vertex);
	
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentShaderCode, NULL);
	glCompileShader(fragment);

	errors::shaderCheck({vertex, fragment});

	programID = glCreateProgram();
	glAttachShader(programID, vertex);
	glAttachShader(programID, fragment);
	glLinkProgram(programID);

	errors::programCheck({programID});

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

ShaderProgram::~ShaderProgram() {
	glDeleteProgram(programID);
}

unsigned ShaderProgram::ID(void) const {
	return this->programID;
}

void ShaderProgram::use(void) const {
	glUseProgram(programID);
}

void ShaderProgram::setBool(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(programID, name.c_str()), (int)value);
}
void ShaderProgram::setInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}
void ShaderProgram::setFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
}

#endif