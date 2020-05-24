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
			this->tiles[j][i] = new Tile(this->defaultTileHeight, this->defaultTileWidth, x, y, color);
		}
	}
}

TileMap::~TileMap() {}

float calculateArea(float v1x, float v2x, float v3x, float v1y, float v2y, float v3y) {
	return abs(
	(v2x - v1x) * (v3y - v1y) -
	(v3x - v1x) * (v2y - v1y)
		) / 2;
}

void TileMap::onMouseClick(double x, double y) {
	// mouse map
	int r = y / (this->defaultTileHeight / 2); // j
	int c = (x - r * (this->defaultTileWidth / 2)) / this->defaultTileWidth; // i


	float x0 = (c * this->defaultTileWidth + r * this->defaultTileHeight);
	float y0 = (r * (this->defaultTileHeight / 2));


	float bx = x0 + (defaultTileWidth / 2);
	float by = y0 + defaultTileHeight;
	
	float ax = x0;
	float ay = y0 + defaultTileWidth / 2;
	
	float dx = x0 + defaultTileWidth / 2;
	float dy = y0;
	
	float cx = x0 + defaultTileWidth;
	float cy = y0 + defaultTileHeight / 2;

	float abd = calculateArea(ax, bx, dx, ay, by, dy);
	float apb = calculateArea(ax, x, bx, ay, y, by);
	float pbd = calculateArea(x, bx, dx, y, by, dy);
	float apd = calculateArea(ax, x, dx, ay, y, dy);

	bool hasCollision = true;
	if (abd == (apb + pbd + apd)) {
		hasCollision = false;
	}
	if (!hasCollision) {
		this->selectedTile = this->tiles[r][c];
		this->selectedTile->setColor(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
	}
}

void TileMap::draw() {
	for (int i = 0; i < this->NUMBER_OF_TILES_VERTICALLY; i++) {
		for (int j = 0; j < this->NUMBER_OF_TILES_HORIZONTALLY; j++) {
			this->tiles[i][j]->draw();
		}
	}

}