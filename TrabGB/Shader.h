#pragma once
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class Shader {
public:
	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
	unsigned int id;
	void use();
};

