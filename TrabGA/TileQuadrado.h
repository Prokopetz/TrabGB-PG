#pragma once
#include <GL/glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Shader.h"
#include "Window.h"

class Tile {
public:
	Tile(float height, float width, float posX, float posY);
	~Tile();
	void draw();

private:
	Shader* shader;
	unsigned int vao;
	float posX;
	float posY;
	float height;
	float width;
};

