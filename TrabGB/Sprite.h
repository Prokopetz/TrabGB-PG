#pragma once
#include "Texture.h"
class Sprite {
public:
	Sprite(int numberOfFrames);
	void addFrame(Texture* texture);
	Texture* getCurrentFrame();
private:
	int numberOfFrames;
	int currentFrame;
	int framesIterator;
	Texture* textures[10];
};

