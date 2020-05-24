#include "TileMap.h"
TileMap::TileMap() {
	this->defaultTileHeight = 32.0f;
	this->defaultTileWidth = 64.0f;

	for (int i = 0; i < this->NUMBER_OF_TILES_VERTICALLY; i++) {
		for (int j = 0; j < this->NUMBER_OF_TILES_HORIZONTALLY; j++) {
			float x = (i * this->defaultTileWidth + j * this->defaultTileHeight);
			float y = (j * (this->defaultTileHeight / 2));

			std::cout << "I: " << i << " J: " << j << "   " << x << "  " << y << std::endl;

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

TileMap::~TileMap() {}

float calculateArea(float v1x, float v2x, float v3x, float v1y, float v2y, float v3y) {
	return abs(
	(v2x - v1x) * (v3y - v1y) -
	(v3x - v1x) * (v2y - v1y)
		) / 2;
}

glm::vec2 tileWalking(int r, int c, int direction) {
	// 1 - north, 2 - sul, 3 - oeste, 4 - leste, 5 - nordeste, 6 - sudeste, 7 - noroeste, 8 sudoeste 
	switch (direction) {
		case 1:
			return glm::vec2(r - 1, c + 2);
		case 2:
			return glm::vec2(r + 1, c - 2);
		case 3:
			return glm::vec2(r - 1, c);
		case 4:
			return glm::vec2(r + 1, c);
		case 5:
			return glm::vec2(r, c + 1);
		case 6:
			return glm::vec2(r + 1, c - 1);
		case 7:
			return glm::vec2(r - 1, c + 1);
		case 8:
			c = c - 1;
			return glm::vec2(r, c);
	}
}

void TileMap::onMouseClick(double x, double y) {
	// mouse map
	// 0 16
	int r = round((x - (2 * y)) / defaultTileWidth);
	int c = (2 * y) / defaultTileHeight;


	float x0 = (r * this->defaultTileWidth + c * this->defaultTileHeight);
	float y0 = (c * (this->defaultTileHeight / 2));


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

	glm::vec2 values = glm::vec2(r, c);
	bool hasCollision = false;
	std::cout << r << "  "<<  c << std::endl;
	if (abd == (apb + pbd + apd) || bcd == (cpb + pbd + cpd)) {
		hasCollision = true;
	}
	if (!hasCollision) {
		int direction;
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
		values = tileWalking(r, c, direction);
	}
	r = int(values.x);
	c = int(values.y);
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


void TileMap::onKeyboardClick(int direction) {
	int r = this->selectedTilePosition.x;
	int c = this->selectedTilePosition.y;
	glm::vec2 values = tileWalking(r, c, direction);
	r = int(values.x);
	c = int(values.y);
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


void TileMap::draw() {
	for (int i = 0; i < this->NUMBER_OF_TILES_VERTICALLY; i++) {
		for (int j = 0; j < this->NUMBER_OF_TILES_HORIZONTALLY; j++) {
			this->tiles[i][j]->draw();
		}
	}
}