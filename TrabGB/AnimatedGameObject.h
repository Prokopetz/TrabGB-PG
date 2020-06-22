#pragma once
#include <chrono>
#include "GameObject.h"
#include "Sprite.h"
using namespace std::chrono;

class AnimatedGameObject : GameObject {
public:
	AnimatedGameObject(float height, float width, Tile* currentTile, const char* texturePath);
	void changeCurrentFrame();
	void draw();
	void addFrame(Texture* texture);
private:
	Sprite* sprite;
	milliseconds lastFrameTime;
};


