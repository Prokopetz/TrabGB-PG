#include "GameManager.h"

GameManager::GameManager() {
	gameOverMenu = new Menu("assets/gameover.jpg");
	winMenu = new Menu("assets/win.jpg");
	this->tileMap = new TileMap();
	hasKey = false;
}

void GameManager::onGameLoop() {
	int tileC = this->tileMap->player->getCurrentTile()->getColumn();
	int tileR = this->tileMap->player->getCurrentTile()->getRow();

	if (tileMap->isPlayerSteppingOnLava(tileC, tileR)) {
		isGameOver = true;
	}

	int portal1Positions[2] = { possiblePortals[portal1][0], possiblePortals[portal1][1] };
	int portal2Positions[2] = { possiblePortals[portal2][0], possiblePortals[portal2][1] };

	if (((tileC == portal1Positions[0] && tileR == portal1Positions[1]) || (tileC == portal2Positions[0] && tileR == portal2Positions[1])) && hasKey) {
		won = true;
	}

	milliseconds now = duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()
	);
	if (now - lastFrameTime >= milliseconds(1000) && hasKey && currentLineBeingTransformed > -1) {
		for (int i = 0; i < 16; i++) {
			tileMap->burnTree(i, currentLineBeingTransformed);
			tileMap->changeTileToLava(i, currentLineBeingTransformed);
		}
		lastFrameTime = duration_cast<milliseconds>(
			system_clock::now().time_since_epoch()
			);
		currentLineBeingTransformed -= 1;
	}
}
void GameManager::draw() {
 	tileMap->draw();
}
void GameManager::onGameOver() {
	gameOverMenu->draw();
}
void GameManager::onGameWin() {
	winMenu->draw();
}
void GameManager::restartGame() {
	this->tileMap = new TileMap();
	this->hasKey = false;
	this->won = false;
	this->isGameOver = false;
	this->currentLineBeingTransformed = 15;
}


void GameManager::onMouseClick(int x, int y) {
	glm::vec2 newPosition = tileMap->onMouseClick(x, y);
	verifyIfPositionIsKeyPosition(newPosition);
}
void GameManager::onKeyboardClick(int direction) {
	glm::vec2 newPosition = tileMap->onKeyboardClick(direction);
	verifyIfPositionIsKeyPosition(newPosition);
}

bool GameManager::verifyIfPositionIsKeyPosition(glm::vec2 newPosition) {
	if (newPosition.x == 0 && newPosition.y == 0) {
		return false;
	}
	int keyColumn = tileMap->keyPosition.x;
	int keyRow = tileMap->keyPosition.y;
	if (newPosition.x == keyColumn && newPosition.y == keyRow && hasKey == false) {
		tileMap->props[keyColumn][keyRow] = nullptr;

		openPortals();
		hasKey = true;
	}
	return hasKey;
}
void GameManager::openPortals() {
	do {
		portal1 = (rand() % 4);
		srand(time(NULL));
		portal2 = (rand() % 4);
	} while (portal1 == portal2);
	


	int portal1Positions[2] = { possiblePortals[portal1][0], possiblePortals[portal1][1] };

	int portal2Positions[2] = { possiblePortals[portal2][0], possiblePortals[portal2][1] };

	tileMap->props[portal1Positions[0]][portal1Positions[1]] = new GameObject(35, 20, tileMap->tiles[portal1Positions[0]][portal1Positions[1]], "assets/portal.png");
	tileMap->props[portal2Positions[0]][portal2Positions[1]] = new GameObject(35, 20, tileMap->tiles[portal2Positions[0]][portal2Positions[1]], "assets/portal.png");
}
