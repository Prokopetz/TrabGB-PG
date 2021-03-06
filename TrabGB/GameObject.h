#pragma once
#include <GL/glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Shader.h"
#include "Texture.h"
#include "Window.h"
#include "Tile.h"

class GameObject {
public:
	GameObject(float height, float width, Tile* currentTile, const char* texturePath);
	~GameObject();
	virtual void draw();
protected:
	Texture* texture;
	Tile* currentTile;
	Shader* shader;
	unsigned int vao;
	float posX;
	float posY;
	float height;
	float width;
};

