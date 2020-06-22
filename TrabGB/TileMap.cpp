#include "TileMap.h"
//NOMES: JOAO DACOL SOARES E NICOLAS GRISA PROKOPETZ

//utils
int textureMapDefault[16][16] = {
{21, 10, 10, 10, 10, 10, 21, 21, 21, 21, 21, 21, 21, 21, 30, 21},
{21, 10, 21, 21, 21, 10, 30, 21, 21, 10, 10, 10, 10, 10, 10, 21},
{21, 10, 21, 21, 21, 10, 21, 21, 21, 10, 21, 21, 21, 21, 10, 21},
{21, 10, 21, 21, 21, 10, 21, 21, 21, 10, 21, 21, 21, 21, 10, 21},
{21, 10, 21, 21, 21, 10, 21, 21, 21, 10, 21, 21, 21, 21, 10, 21},
{21, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 21, 21, 10, 21},
{21, 10, 21, 21, 21, 21, 21, 30, 30, 30, 21, 10, 21, 21, 10, 21},
{21, 10, 21, 21, 21, 21, 21, 30, 31, 30, 21, 10, 21, 21, 10, 21},
{21, 10, 10, 10, 10, 21, 21, 30, 30, 30, 21, 10, 21, 21, 21, 21},
{30, 21, 21, 21, 10, 10, 10, 10, 10, 10, 10, 10, 21, 21, 21, 21},
{10, 21, 21, 21, 10, 21, 10, 21, 21, 21, 21, 10, 21, 21, 10, 21},
{10, 21, 21, 21, 10, 21, 10, 21, 21, 21, 21, 10, 10, 10, 10, 10},
{10, 10, 10, 10, 10, 21, 10, 10, 10, 10, 10, 10, 21, 10, 21, 21},
{21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 10, 21, 21},
{10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 30, 21},
{21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21}
};

int textureMap[16][16];
bool hasCollisionWithProp(int nextColumn, int nextRow) {
	if (textureMap[nextColumn][nextRow] == 21) {
		return true;
	}
	return false;
}
TileSet* tileSet;

// public
TileMap::TileMap() {
	tileSet = new TileSet("assets/handpainted.png", 4, 4);
	this->defaultTileHeight = 32.0f;
	this->defaultTileWidth = 64.0f;
	for (int i = 0; i < this->NUMBER_OF_TILES_VERTICALLY; i++) {
		for (int j = 0; j < this->NUMBER_OF_TILES_HORIZONTALLY; j++) {
			textureMap[i][j] = textureMapDefault[i][j];
		}
	}
	this->diamondView = new DiamondView(defaultTileHeight, defaultTileWidth, NUMBER_OF_TILES_VERTICALLY, NUMBER_OF_TILES_HORIZONTALLY);

	for (int i = 0; i < this->NUMBER_OF_TILES_VERTICALLY; i++) {
		for (int j = 0; j < this->NUMBER_OF_TILES_HORIZONTALLY; j++) {
			int x = diamondView->getTileXPositionFromMatrix(i, j);
			int y = diamondView->getTileYPositionFromMatrix(i, j);
			int id = textureMap[j][i];
			glm::vec2 offset = tileSet->getTile(id);
			this->tiles[i][j] = new Tile(this->defaultTileHeight, this->defaultTileWidth, x, y, offset, 0, tileSet->getNormalizedTextureWidth(), tileSet->getNormalizedTextureHeight());
			this->tiles[i][j]->setColumn(i);
			this->tiles[i][j]->setRow(j);
		}
	}
	tileSet->unbindTexture();

	this->player = new Player(40, 25, this->tiles[0][14]);

	for (int i = 0; i < this->NUMBER_OF_TILES_VERTICALLY; i++) {
		for (int j = this->NUMBER_OF_TILES_HORIZONTALLY; j >= 0; j--) {
			if (textureMap[j][i] == 21) {
				props[i][j] = new GameObject(60, 45, tiles[i][j], "assets/tree.png");
			}
		}
	}
	this->keyPosition = glm::vec2(8, 7);
	props[8][7] = new GameObject(30, 30, tiles[8][7], "assets/key.png");
	props[6][1] = new GameObject(35, 20, tiles[6][1], "assets/portal_desligado.png");
	props[0][9] = new GameObject(35, 20, tiles[0][9], "assets/portal_desligado.png");
	props[14][14] = new GameObject(35, 20, tiles[14][14], "assets/portal_desligado.png");
	props[14][0] = new GameObject(35, 20, tiles[14][0], "assets/portal_desligado.png");
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
	for (int i = 0; i < this->NUMBER_OF_TILES_VERTICALLY; i++) {
		for (int j = 0; j < this->NUMBER_OF_TILES_HORIZONTALLY; j++) {
			if (props[j][i]) {
				props[j][i]->draw();
			}
		}
	}
}

glm::vec2 TileMap::onMouseClick(double x, double y) {
	glm::vec2 tileMatrixPosition = diamondView->getRowAndColumnForMousePositionClick(x, y);
	if (!diamondView->hasCollision(x, y)) {
		tileMatrixPosition = diamondView->tileWalkingToCorrectDirection(x, y);
	}
	if (!this->isValidStep(tileMatrixPosition)) {
		return glm::vec2();
	}
	this->changePlayerDirection(tileMatrixPosition);
	this->changeSelectedTileIfNeeded(tileMatrixPosition);
	return tileMatrixPosition;
}
glm::vec2 TileMap::onKeyboardClick(int direction) {
	int r = this->player->getCurrentTile()->getColumn();
	int c = this->player->getCurrentTile()->getRow();
	glm::vec2 values = diamondView->tileWalking(r, c, direction);
	if (hasCollisionWithProp(values.y, values.x)) {
		return glm::vec2();
	}
	this->player->changeDirection(direction);
	this->changeSelectedTileIfNeeded(values);
	return values;
}

void TileMap::changeTileToLava(int c, int r) {
	textureMap[r][c] = 1;
	glm::vec2 offset = tileSet->getTile(1);
	int posX = this->tiles[c][r]->getPosX();
	int posY = this->tiles[c][r]->getPosY();

	int col = this->tiles[c][r]->getColumn();
	int row = this->tiles[c][r]->getRow();
	this->tiles[c][r] = new Tile(this->defaultTileHeight, this->defaultTileWidth, posX, posY, offset, 0, tileSet->getNormalizedTextureWidth(), tileSet->getNormalizedTextureHeight());
	this->tiles[c][r]->setColumn(col);
	this->tiles[c][r]->setRow(row);

}
void TileMap::changeSelectedTileIfNeeded(glm::vec2 tileMatrixPosition) {
	int r = int(tileMatrixPosition.x);
	int c = int(tileMatrixPosition.y);
	if (r < NUMBER_OF_TILES_VERTICALLY && c < NUMBER_OF_TILES_HORIZONTALLY && r >= 0 && c >= 0) {
		this->player->setCurrentTile(this->tiles[r][c]);
	}
}
void TileMap::changePlayerDirection(glm::vec2 tileMatrixPosition) {
	int currentRow = this->player->getCurrentTile()->getColumn();
	int currentColumn = this->player->getCurrentTile()->getRow();
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
void TileMap::burnTree(int c, int r) {
	if (textureMap[r][c] == 21) {
		AnimatedGameObject* burningTree = new AnimatedGameObject(60, 45, tiles[c][r]);

		props[c][r] = (GameObject*) burningTree;
	}
}

bool TileMap::isPlayerSteppingOnLava(int c, int r) {
	if (textureMap[r][c] == 1) {
		return true;
	}
	return false;
}
bool TileMap::isValidStep(glm::vec2 tileMatrixPosition) {
	int currentRow = this->player->getCurrentTile()->getColumn();
	int currentColumn = this->player->getCurrentTile()->getRow();
	int nextRow = tileMatrixPosition.x;
	int nextColumn = tileMatrixPosition.y;

	if (hasCollisionWithProp(nextColumn, nextRow)) {
		return false;
	}
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

TileMap::~TileMap() {}

