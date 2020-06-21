#pragma once
#include <glm.hpp>
#include "Player.h"
class DiamondView {
public:
	DiamondView(int defaultTileHeight, int defaultTileWidth, int numberOfTilesVertically, int numberOfTilesHorizontally);
	glm::vec2 tileWalking(int r, int c, int direction);
	glm::vec2 tileWalkingToCorrectDirection(int r, int c);
	glm::vec2 getRowAndColumnForMousePositionClick(int x, int y);
	int getTileXPositionFromMatrix(int r, int c);
	int getTileYPositionFromMatrix(int r, int c);
	bool hasCollision(int x, int y);
private:
	int defaultTileHeight;
	int defaultTileWidth;
	int numberOfTilesVertically;
	int numberOfTilesHorizontally;

};

