#pragma once
#include "GameObject.h"
#include "Tile.h"
class Player : public GameObject {
public:
	static const int NORTH_WEST = 0;
	static const int NORTH_EAST = 1;
	static const int SOUTH_WEST = 2;
	static const int SOUTH_EAST = 3;
	Player(float height, float width, Tile* currentTile);
	void setCurrentTile(Tile* selectedTile);
	void changeDirection(int direction);
	Tile* getCurrentTile();
private:
	Texture* textures[4];
};

