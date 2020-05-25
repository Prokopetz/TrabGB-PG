#include "Shader.h"
//NOMES: JOAO DACOL SOARES E NICOLAS GRISA PROKOPETZ

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
	std::string vertexString;
	std::string fragmentString;

	std::ifstream vertexFile;
	std::ifstream fragmentFile;

	try {
		vertexFile.open(vertexShaderPath);
		fragmentFile.open(fragmentShaderPath);

		std::stringstream vertexStream;
		std::stringstream fragmentStream;
		vertexStream << vertexFile.rdbuf();
		fragmentStream << fragmentFile.rdbuf();

		vertexString = vertexStream.str();
		fragmentString = fragmentStream.str();

	}
	catch (std::ifstream::failure exception) {
		std::cout << "Error reading shaders" << std::endl;
	}

	const char* vertexCode = vertexString.c_str();
	const char* fragmentCode = fragmentString.c_str();

	// Compile shaders

	unsigned int vertex;
	unsigned int fragment;

	int success;
	char infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexCode, NULL);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "Error while compiling shaders" << infoLog << std::endl;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentCode, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "Error while compiling shaders" << infoLog << std::endl;
	}

	this->id = glCreateProgram();
	glAttachShader(this->id, vertex);
	glAttachShader(this->id, fragment);
	glLinkProgram(this->id);

	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use() {
	glUseProgram(this->id);
}

