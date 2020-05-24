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
	void onMouseClick(double x, double y);
private:
	Tile* tiles[NUMBER_OF_TILES_VERTICALLY][NUMBER_OF_TILES_HORIZONTALLY];
	float defaultTileHeight;
	float defaultTileWidth;
	Tile* selectedTile;
};

