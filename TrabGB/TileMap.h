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
	glm::vec2 onMouseClick(double x, double y);
	glm::vec2 onKeyboardClick(int direction);
	Player* player;
	int getTileXPositionFromMatrix(int r, int c);
	int getTileYPositionFromMatrix(int r, int c);
	bool hasCollision(int x, int y);
	glm::vec2 tileWalkingToCorrectDirection(int x, int y);
	glm::vec2 tileWalking(int r, int c, int direction);
	void changeSelectedTileIfNeeded(glm::vec2 tileMatrixPosition);
	glm::vec2 getRowAndColumnForMousePositionClick(int x, int y);
	void changePlayerDirection(glm::vec2 tileMatrixPosition);
	bool isValidStep(glm::vec2 tileMatrixPosition);
	void changeTileToLava(int c, int r);
	bool isPlayerSteppingOnLava(int c, int r);
	Tile* tiles[NUMBER_OF_TILES_VERTICALLY][NUMBER_OF_TILES_HORIZONTALLY];
	float defaultTileHeight;
	float defaultTileWidth;
	Tile* selectedTile;
	glm::vec4 lastSelectedTileColor;
	glm::vec2 selectedTilePosition;
	GameObject* props[NUMBER_OF_TILES_VERTICALLY][NUMBER_OF_TILES_HORIZONTALLY];
	glm::vec2 keyPosition;
};

