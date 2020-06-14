#include "TileSet.h"
TileSet::TileSet(const char* filename, int rows, int columns) {
	this->columns = columns;
	this->rows = rows;
	this->texture = new Texture(filename);
	texture->bind();
}

void TileSet::bindTexture() {
	this->texture->bind();
}

void TileSet::unbindTexture() {
	this->texture->unbind();
}

glm::vec2 TileSet::getTile(int id) {
	int c = id % 10;
	int r = (id - (id % 10)) / 10;
	return glm::vec2(c, r);
}

int TileSet::getTextureId() {
	return this->texture->getId();
}

float TileSet::getNormalizedTextureWidth() {
	float imageWidth = this->texture->getImageWidth();
	float textureWidth = imageWidth / this->columns;
	return textureWidth / imageWidth;
}

float TileSet::getNormalizedTextureHeight() {
	float imageHeight = this->texture->getImageHeight();
	float textureHeight = imageHeight / this->rows;
	return textureHeight / imageHeight;
}
