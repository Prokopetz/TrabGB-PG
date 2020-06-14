#pragma once
#include <GL/glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Shader.h"
#include "Window.h"
#include "Texture.h"

class Tile {
public:
	Tile(float height, float width, float posX, float posY, glm::vec2 offset, int textureId, float textureWidth, float textureHeight);
	~Tile();
	void draw();
	float getPosX();
	float getPosY();

private:
	Shader* shader;
	unsigned int vao;
	int textureId;
	float posX;
	float posY;
	float height;
	float width;
	Texture* texture;
};

