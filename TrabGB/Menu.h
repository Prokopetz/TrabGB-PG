#pragma once
#include <GL/glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Shader.h"
#include "Texture.h"
#include "Window.h"

class Menu {
public:
	Menu(const char* texturePath);
	void draw();
private:
	Shader* shader;
	Texture* texture;
	unsigned int vao;
	int textureId;

};

