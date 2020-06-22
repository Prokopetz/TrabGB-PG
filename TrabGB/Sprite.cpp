#include "Sprite.h"
Sprite::Sprite(int numberOfFrames) {
	currentFrame = 0;
	framesIterator = 0;
	this->numberOfFrames = numberOfFrames;
}

void Sprite::addFrame(Texture* texture) {
	textures[framesIterator] = texture;
	framesIterator++;
}

Texture* Sprite::getCurrentFrame() {
	if (currentFrame == numberOfFrames - 1) {
		currentFrame = 0;
	}
	Texture* currentTexture = textures[currentFrame];
	currentFrame++;
	return currentTexture;
}