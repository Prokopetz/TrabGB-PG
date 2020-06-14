#include "Player.h"


Player::Player(float height, float width, Tile* currentTile) : GameObject(height, width, currentTile, "assets/Nordeste.png") {
	this->textures[NORTH_WEST] = new Texture("assets/Noroeste.png");
	this->textures[NORTH_EAST] = new Texture("assets/Nordeste.png");
	this->textures[SOUTH_WEST] = new Texture("assets/Sudoeste.png");
	this->textures[SOUTH_EAST] = new Texture("assets/Sudeste.png");
}

void Player::changeDirection(int direction) {
	this->texture = this->textures[direction];
}

void Player::setCurrentTile(Tile* selectedTile) {
	this->currentTile = selectedTile;
}

