#include "DiamondView.h"
//util
float calculateArea(float v1x, float v2x, float v3x, float v1y, float v2y, float v3y) {
	return abs(
	(v2x - v1x) * (v3y - v1y) -
	(v3x - v1x) * (v2y - v1y)
		) / 2;
}

DiamondView::DiamondView(int defaultTileHeight, int defaultTileWidth, int numberOfTilesVertically, int numberOfTilesHorizontally) {
	this->defaultTileHeight = defaultTileHeight;
	this->defaultTileWidth = defaultTileWidth;
	this->numberOfTilesVertically = numberOfTilesVertically;
	this->numberOfTilesHorizontally = numberOfTilesHorizontally;
}

glm::vec2 DiamondView::tileWalking(int r, int c, int direction) {
	// 1 - north, 2 - sul, 3 - oeste, 4 - leste, 5 - nordeste, 6 - sudeste, 7 - noroeste, 8 sudoeste 
	switch (direction) {
	case Player::NORTH_EAST:
		return glm::vec2(r + 1, c);
	case Player::SOUTH_EAST:
		return glm::vec2(r, c + 1);
	case Player::NORTH_WEST:
		return glm::vec2(r, c - 1);
	case Player::SOUTH_WEST:
		return glm::vec2(r - 1, c);
	}
}

glm::vec2 DiamondView::tileWalkingToCorrectDirection(int x, int y) {
	glm::vec2 tileMatrixPosition = this->getRowAndColumnForMousePositionClick(x, y);
	int r = tileMatrixPosition.x;
	int c = tileMatrixPosition.y;
	float x0 = this->getTileXPositionFromMatrix(r, c);
	float y0 = this->getTileYPositionFromMatrix(r, c);

	float bx = x0 + (defaultTileWidth / 2);

	float ay = y0 + defaultTileHeight / 2;

	float dx = x0 + defaultTileWidth / 2;

	float cy = y0 + defaultTileHeight / 2;

	int direction = 0;
	if (x > bx && y > cy) {
		direction = 1;
		std::cout << "direita cima" << std::endl;
	}
	else if (x < bx && y > ay) {
		direction = 0;
		std::cout << "esquerda cima" << std::endl;
	}
	else if (x < dx && y < ay) {
		direction = 2;
		std::cout << "esquerda baixo" << std::endl;
	}
	else if (x > dx && y < cy) {
		direction = 3;
		std::cout << "direita baixo" << std::endl;
	}
	return tileWalking(r, c, direction);
}

glm::vec2 DiamondView::getRowAndColumnForMousePositionClick(int x, int y) {
	int offset = (this->defaultTileHeight * this->numberOfTilesVertically / 1.3) - this->defaultTileHeight / 2;
	int c = round((2 * x / this->defaultTileWidth - 2 * (y - offset) / this->defaultTileHeight) / 2);
	int r = floor(2 * (y - offset) / this->defaultTileHeight + c);
	std::cout << r << c << std::endl;
	return glm::vec2(r, c);
}

int DiamondView::getTileXPositionFromMatrix(int r, int c) {
	return this->defaultTileWidth / 2 * (c + r);
}

int DiamondView::getTileYPositionFromMatrix(int r, int c) {
	return  (this->defaultTileHeight / 2 * (r - c)) + (this->defaultTileHeight * this->numberOfTilesVertically / 1.3) - this->defaultTileHeight / 2;
}

bool DiamondView::hasCollision(int x, int y) {
	glm::vec2 rowAndColumn = this->getRowAndColumnForMousePositionClick(x, y);
	int r = rowAndColumn.x;
	int c = rowAndColumn.y;

	float x0 = this->getTileXPositionFromMatrix(r, c);
	float y0 = this->getTileYPositionFromMatrix(r, c);

	float bx = x0 + (defaultTileWidth / 2);
	float by = y0 + defaultTileHeight;

	float ax = x0;
	float ay = y0 + defaultTileHeight / 2;

	float dx = x0 + defaultTileWidth / 2;
	float dy = y0;

	float cx = x0 + defaultTileWidth;
	float cy = y0 + defaultTileHeight / 2;

	float abd = calculateArea(ax, bx, dx, ay, by, dy);
	float apb = calculateArea(ax, x, bx, ay, y, by);
	float pbd = calculateArea(x, bx, dx, y, by, dy);
	float apd = calculateArea(ax, x, dx, ay, y, dy);

	float bcd = calculateArea(bx, cx, dx, by, cy, dy);
	float cpb = calculateArea(cx, x, bx, cy, y, by);
	float cpd = calculateArea(cx, x, dx, cy, y, dy);

	return (abd == (apb + pbd + apd) || bcd == (cpb + pbd + cpd));
}