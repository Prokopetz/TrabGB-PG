#pragma once
#include <GL/glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <chrono>
#include "TileMap.h"
#include "Menu.h"
using namespace std::chrono;

class GameManager {
public:
	GameManager();
	void onMouseClick(int x, int y);
	void onKeyboardClick(int direction);
	void onGameLoop();
	void onGameOver();
	void draw();
	void restartGame();
	bool isGameOver = false;
	bool won = false;
private:
	Menu* gameOverMenu;
	TileMap* tileMap;
	bool hasKey;
	bool verifyIfPositionIsKeyPosition(glm::vec2 newPosition);
	void openPortals();
	milliseconds lastFrameTime;
	int currentLineBeingTransformed = 15;
	int possiblePortals[4][2] = { {6,1}, {0,9}, {14,14}, {15,0} };
	int portal1;
	int portal2;

};

