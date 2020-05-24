#include "TileMap.h"

TileMap::TileMap() {


	for (int i = 0; i < this->NUMBER_OF_TILES_VERTICALLY; i++) {
		for (int j = 0; j < this->NUMBER_OF_TILES_HORIZONTALLY; j++) {
			float x = j * 64 + i * 32;
			float y = i * 16;
			this->tiles[i][j] = new Tile(32.0, 64.0, x, y);
		}
	}
}

TileMap::~TileMap() {}

void TileMap::draw() {
	for (int i = 0; i < this->NUMBER_OF_TILES_VERTICALLY; i++) {
		for (int j = 0; j < this->NUMBER_OF_TILES_HORIZONTALLY; j++) {
			this->tiles[i][j]->draw();
		}
	}

}