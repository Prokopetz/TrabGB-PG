#pragma once
#include <chrono>
#include "GameObject.h"
#include "Sprite.h"
using namespace std::chrono;

class AnimatedGameObject : GameObject {
public:
	AnimatedGameObject(float height, float width, Tile* currentTile);
	void changeCurrentFrame();
	void draw();
private:
	Sprite* sprite;
	milliseconds lastFrameTime;
};


