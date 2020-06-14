#pragma once
#include "TileMap.h"
#include <GL/glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
class GameManager {
public:
	GameManager();
	void onMouseClick(int x, int y);
	void onKeyboardClick(int direction);
	void draw();
private:
	TileMap* tileMap;
	bool hasKey;
};

