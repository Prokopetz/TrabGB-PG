#include "TileSet.h"
TileSet::TileSet(const char* filename, int rows, int columns) {
	this->columns = columns;
	this->rows = rows;
	this->texture = new Texture("assets/texture.jpg");
	texture->bind(0);
}
glm::vec2 TileSet::getTile(int id) {
	int c = id % columns;
	int r = id / rows;
	return glm::vec2(c, r);
}
