#include "GameManager.h"

GameManager::GameManager() {
	this->tileMap = new TileMap();
	hasKey = false;
}

void GameManager::onMouseClick(int x, int y) {
	glm::vec2 newPosition = tileMap->onMouseClick(x, y);
	if (newPosition.x == 0 && newPosition.y == 0) {
		return;
	}
	int keyColumn = tileMap->keyPosition.x;
	int keyRow = tileMap->keyPosition.y;
	if (newPosition.x == keyColumn && newPosition.y == keyRow) {
		tileMap->props[keyColumn][keyRow] = nullptr;
		hasKey = true;
	}
}

void GameManager::onKeyboardClick(int direction) {
	glm::vec2 newPosition = tileMap->onKeyboardClick(direction);
}

void GameManager::draw() {
	tileMap->draw();
}