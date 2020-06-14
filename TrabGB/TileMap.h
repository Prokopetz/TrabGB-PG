#pragma once
#include <vector>
#include "Tile.h"
#include "TileSet.h"
#include "GameObject.h"
#include "Player.h"
class TileMap {
public:
	static const int NUMBER_OF_TILES_HORIZONTALLY = 16;
	static const int NUMBER_OF_TILES_VERTICALLY = 16;
	TileMap();
	~TileMap();
	void draw();
	void onMouseClick(double x, double y);
	void onKeyboardClick(int direction);
private:
	Player* player;
	int getTileXPositionFromMatrix(int r, int c);
	int getTileYPositionFromMatrix(int r, int c);
	bool hasCollision(int x, int y);
	glm::vec2 tileWalkingToCorrectDirection(int x, int y);
	glm::vec2 tileWalking(int r, int c, int direction);
	void changeSelectedTileIfNeeded(glm::vec2 tileMatrixPosition);
	glm::vec2 getRowAndColumnForMousePositionClick(int x, int y);
	Tile* tiles[NUMBER_OF_TILES_VERTICALLY][NUMBER_OF_TILES_HORIZONTALLY];
	float defaultTileHeight;
	float defaultTileWidth;
	Tile* selectedTile;
	glm::vec4 lastSelectedTileColor;
	glm::vec2 selectedTilePosition;
};

