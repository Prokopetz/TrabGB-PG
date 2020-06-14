#pragma once
#include <string.h>
#include "Texture.h"
#include <glm.hpp>

class TileSet {
public:
	TileSet(const char* filename, int rows, int columns);
	glm::vec2 getTile(int id);
	int getTextureId();
	float getNormalizedTextureWidth();
	float getNormalizedTextureHeight();
	void bindTexture();
	void unbindTexture();
private:
	int textureId;
	int columns;
	int rows;
	Texture* texture;
};

