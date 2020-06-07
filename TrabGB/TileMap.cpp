#include "TileMap.h"
//NOMES: JOAO DACOL SOARES E NICOLAS GRISA PROKOPETZ

//util
float calculateArea(float v1x, float v2x, float v3x, float v1y, float v2y, float v3y) {
	return abs(
	(v2x - v1x) * (v3y - v1y) -
	(v3x - v1x) * (v2y - v1y)
		) / 2;
}
// public
TileMap::TileMap() {
	this->defaultTileHeight = 32.0f;
	this->defaultTileWidth = 64.0f;

	for (int i = 0; i < this->NUMBER_OF_TILES_VERTICALLY; i++) {
		for (int j = 0; j < this->NUMBER_OF_TILES_HORIZONTALLY; j++) {
			int x = this->getTileXPositionFromMatrix(i, j);
			int y = this->getTileYPositionFromMatrix(i, j);
			float randomR = rand() / float(RAND_MAX);
			float randomG = rand() / float(RAND_MAX);
			float randomB = rand() / float(RAND_MAX);
			glm::vec4 color = glm::vec4(randomR, randomG, randomB, 1.0f);
			this->tiles[i][j] = new Tile(this->defaultTileHeight, this->defaultTileWidth, x, y, color);
		}
	}
	this->selectedTilePosition = glm::vec2(0, 0);
	this->selectedTile = this->tiles[0][0];
	this->lastSelectedTileColor = this->selectedTile->getColor();
	this->selectedTile->setColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
}

void TileMap::onMouseClick(double x, double y) {
	glm::vec2 tileMatrixPosition = this->getRowAndColumnForMousePositionClick(x, y);
	if (!this->hasCollision(x, y)) {
		tileMatrixPosition = tileWalkingToCorrectDirection(x, y);
	}
	this->changeSelectedTileIfNeeded(tileMatrixPosition);
}

void TileMap::onKeyboardClick(int direction) {
	int r = this->selectedTilePosition.x;
	int c = this->selectedTilePosition.y;
	glm::vec2 values = tileWalking(r, c, direction);
	this->changeSelectedTileIfNeeded(values);
}

void TileMap::draw() {
	for (int i = 0; i < this->NUMBER_OF_TILES_VERTICALLY; i++) {
		for (int j = 0; j < this->NUMBER_OF_TILES_HORIZONTALLY; j++) {
			this->tiles[i][j]->draw();
		}
	}
}

//private

int TileMap::getTileXPositionFromMatrix(int r, int c) {
	//return r * this->defaultTileWidth + c * this->defaultTileHeight;
	return this->defaultTileWidth / 2 * (c + r);
}

int TileMap::getTileYPositionFromMatrix(int r, int c) {
	/*return c * (this->defaultTileHeight / 2);*/
	return  (this->defaultTileHeight / 2 * (r - c)) + (this->defaultTileHeight * this->NUMBER_OF_TILES_VERTICALLY / 1.3) - this->defaultTileHeight / 2;

}


bool TileMap::hasCollision(int x, int y) {
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

glm::vec2 TileMap::tileWalkingToCorrectDirection(int x, int y) {
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
		direction = 5;
		std::cout << "direita cima" << std::endl;
	}
	else if (x < bx && y > ay) {
		direction = 7;
		std::cout << "esquerda cima" << std::endl;
	}
	else if (x < dx && y < ay) {
		direction = 8;
		std::cout << "esquerda baixo" << std::endl;
	}
	else if (x > dx && y < cy) {
		direction = 6;
		std::cout << "direita baixo" << std::endl;
	}
	return tileWalking(r, c, direction);
}

glm::vec2 TileMap::tileWalking(int r, int c, int direction) {
	// 1 - north, 2 - sul, 3 - oeste, 4 - leste, 5 - nordeste, 6 - sudeste, 7 - noroeste, 8 sudoeste 
	switch (direction) {
	case 1:
		return glm::vec2(r + 1, c - 1);
	case 2:
		return glm::vec2(r - 1, c + 1);
	case 3:
		return glm::vec2(r - 1, c - 1);
	case 4:
		return glm::vec2(r + 1, c + 1);
	case 5:
		return glm::vec2(r + 1, c);
	case 6:
		return glm::vec2(r, c + 1);
	case 7:
		return glm::vec2(r, c - 1);
	case 8:
		return glm::vec2(r - 1, c);
	}
}

void TileMap::changeSelectedTileIfNeeded(glm::vec2 tileMatrixPosition) {
	int r = int(tileMatrixPosition.x);
	int c = int(tileMatrixPosition.y);
	if (r < NUMBER_OF_TILES_VERTICALLY && c < NUMBER_OF_TILES_HORIZONTALLY && r >= 0 && c >= 0) {
		this->selectedTilePosition = glm::vec2(r, c);
		if (this->selectedTile != nullptr) {
			this->selectedTile->setColor(this->lastSelectedTileColor);
		}
		this->selectedTile = this->tiles[r][c];
		this->lastSelectedTileColor = this->selectedTile->getColor();
		this->selectedTile->setColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	}
}
//offset
//(
glm::vec2 TileMap::getRowAndColumnForMousePositionClick(int x, int y) {
	int offset = (this->defaultTileHeight * this->NUMBER_OF_TILES_VERTICALLY / 1.3) - this->defaultTileHeight / 2;
	int c = round((2 * x / this->defaultTileWidth - 2 * (y - offset) / this->defaultTileHeight) / 2);
	int r = floor(2 * (y - offset) / this->defaultTileHeight + c);
	std::cout << r << c << std::endl;
	return glm::vec2(r, c);
}


TileMap::~TileMap() {}

