#pragma once
#include "TileMap.h"
#include <GL/glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <chrono>

using namespace std::chrono;

class GameManager {
public:
	GameManager();
	void onMouseClick(int x, int y);
	void onKeyboardClick(int direction);
	void draw();
private:
	TileMap* tileMap;
	bool hasKey;
	bool verifyIfPositionIsKeyPosition(glm::vec2 newPosition);
	void openPortals();
	milliseconds lastFrameTime;
	int currentLineBeingTransformed = 15;
};

