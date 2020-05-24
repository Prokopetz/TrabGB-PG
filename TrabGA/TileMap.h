#pragma once
#include <vector>
#include "Tile.h"

class TileMap {
public:
	static const int NUMBER_OF_TILES_HORIZONTALLY = 5;
	static const int NUMBER_OF_TILES_VERTICALLY = 5;
	TileMap();
	~TileMap();
	void draw();
private:
	Tile* tiles[NUMBER_OF_TILES_VERTICALLY][NUMBER_OF_TILES_HORIZONTALLY];
};

