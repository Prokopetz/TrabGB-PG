#pragma once
#include <GL/glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Shader.h"
#include "Window.h"

class Tile {
public:
	Tile(float height, float width, float posX, float posY, glm::vec4 color);
	~Tile();
	void draw();
	void setColor(glm::vec4 color);
	glm::vec4 getColor();

private:
	Shader* shader;
	unsigned int vao;
	float posX;
	float posY;
	float height;
	float width;
	glm::vec4 color;
};

