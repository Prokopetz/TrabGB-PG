#include "TileMap.h"
//NOMES: JOAO DACOL SOARES E NICOLAS GRISA PROKOPETZ
int textureMap[16][16] = {
{10, 10, 10, 10, 10, 10, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21},
{10, 21, 21, 21, 21, 10, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21},
{10, 21, 21, 21, 21, 10, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21},
{10, 21, 21, 21, 21, 10, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21},
{10, 21, 21, 21, 21, 10, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21},
{10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 21, 21, 21, 21},
{10, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21},
{10, 21, 21, 21, 21, 21, 10, 10, 10, 21, 21, 21, 21, 21, 21, 21},
{10, 10, 10, 10, 10, 21, 10, 21, 10, 21, 21, 21, 21, 21, 21, 21},
{21, 21, 21, 21, 10, 10, 10, 21, 10, 10, 10, 10, 21, 21, 21, 21},
{21, 21, 21, 21, 10, 21, 10, 21, 21, 21, 21, 21, 21, 21, 21, 21},
{21, 21, 21, 21, 10, 21, 10, 21, 21, 21, 21, 10, 10, 10, 10, 10},
{10, 10, 10, 10, 10, 21, 10, 10, 10, 10, 10, 10, 21, 10, 21, 21},
{21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 10, 21, 21},
{10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 21, 21},
{21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21}
};
TileSet* tileSet;
//util
float calculateArea(float v1x, float v2x, float v3x, float v1y, float v2y, float v3y) {
	return abs(
	(v2x - v1x) * (v3y - v1y) -
	(v3x - v1x) * (v2y - v1y)
		) / 2;
}
// public
TileMap::TileMap() {
	tileSet = new TileSet("assets/handpainted.png", 4, 4);
	this->defaultTileHeight = 32.0f;
	this->defaultTileWidth = 64.0f;

	for (int i = 0; i < this->NUMBER_OF_TILES_VERTICALLY; i++) {
		for (int j = 0; j < this->NUMBER_OF_TILES_HORIZONTALLY; j++) {
			int x = this->getTileXPositionFromMatrix(i, j);
			int y = this->getTileYPositionFromMatrix(i, j);
			int id = textureMap[j][i];
			glm::vec2 offset = tileSet->getTile(id);
			this->tiles[i][j] = new Tile(this->defaultTileHeight, this->defaultTileWidth, x, y, offset, 0, tileSet->getNormalizedTextureWidth(), tileSet->getNormalizedTextureHeight());
		}
	}
	tileSet->unbindTexture();


	this->player = new Player(75, 50, this->tiles[0][0]);


	this->selectedTilePosition = glm::vec2(0, 0);
	this->selectedTile = this->tiles[0][0];
}

void TileMap::onMouseClick(double x, double y) {
	glm::vec2 tileMatrixPosition = this->getRowAndColumnForMousePositionClick(x, y);
	if (!this->hasCollision(x, y)) {
		tileMatrixPosition = tileWalkingToCorrectDirection(x, y);
	}
	if (!this->isValidStep(tileMatrixPosition)) {
		return;
	}
	this->changePlayerDirection(tileMatrixPosition);
	this->changeSelectedTileIfNeeded(tileMatrixPosition);
}


void TileMap::onKeyboardClick(int direction) {
	int r = this->selectedTilePosition.x;
	int c = this->selectedTilePosition.y;
	glm::vec2 values = tileWalking(r, c, direction);
	this->player->changeDirection(direction);
	this->changeSelectedTileIfNeeded(values);
}

void TileMap::draw() {
	tileSet->bindTexture();
	for (int i = 0; i < this->NUMBER_OF_TILES_VERTICALLY; i++) {
		for (int j = 0; j < this->NUMBER_OF_TILES_HORIZONTALLY; j++) {
			this->tiles[i][j]->draw();
		}
	}
	tileSet->unbindTexture();
	player->draw();
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

glm::vec2 TileMap::tileWalking(int r, int c, int direction) {
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

void TileMap::changeSelectedTileIfNeeded(glm::vec2 tileMatrixPosition) {
	int r = int(tileMatrixPosition.x);
	int c = int(tileMatrixPosition.y);
	if (r < NUMBER_OF_TILES_VERTICALLY && c < NUMBER_OF_TILES_HORIZONTALLY && r >= 0 && c >= 0) {
		this->selectedTilePosition = glm::vec2(r, c);
		if (this->selectedTile != nullptr) {
		}
		this->selectedTile = this->tiles[r][c];
		this->player->setCurrentTile(selectedTile);

	}
}

glm::vec2 TileMap::getRowAndColumnForMousePositionClick(int x, int y) {
	int offset = (this->defaultTileHeight * this->NUMBER_OF_TILES_VERTICALLY / 1.3) - this->defaultTileHeight / 2;
	int c = round((2 * x / this->defaultTileWidth - 2 * (y - offset) / this->defaultTileHeight) / 2);
	int r = floor(2 * (y - offset) / this->defaultTileHeight + c);
	std::cout << r << c << std::endl;
	return glm::vec2(r, c);
}

bool TileMap::isValidStep(glm::vec2 tileMatrixPosition) {
	int currentRow = this->selectedTilePosition.x;
	int currentColumn = this->selectedTilePosition.y;
	int nextRow = tileMatrixPosition.x;
	int nextColumn = tileMatrixPosition.y;

	if (currentColumn != nextColumn && currentRow != nextRow) {
		return false;
	}
	if (currentColumn + 1 < nextColumn || currentColumn > nextColumn + 1) {
		return false;
	}
	if (currentRow + 1 < nextRow || currentRow > nextRow + 1) {
		return false;
	}
	return true;
}

void TileMap::changePlayerDirection(glm::vec2 tileMatrixPosition) {
	int currentRow = this->selectedTilePosition.x;
	int currentColumn = this->selectedTilePosition.y;
	int nextRow = tileMatrixPosition.x;
	int nextColumn = tileMatrixPosition.y;
	if (nextRow == currentRow && nextColumn > currentColumn) {
		this->player->changeDirection(Player::SOUTH_EAST);
	}
	if (nextRow == currentRow && nextColumn < currentColumn) {
		this->player->changeDirection(Player::NORTH_WEST);
	}
	if (nextColumn == currentColumn && nextRow > currentRow) {
		this->player->changeDirection(Player::NORTH_EAST);
	}
	if (nextColumn == currentColumn && nextRow < currentRow) {
		this->player->changeDirection(Player::SOUTH_WEST);
	}
}

TileMap::~TileMap() {}

