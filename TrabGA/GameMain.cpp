#include <iostream>
#include "Tile.h"
#include "Window.h"
#include "TileMap.h"
int main() {
    Window* window = new Window();

    TileMap* tileMap = new TileMap();

    while (!window->shouldCloseProgram()) {
        window->onBeforeRender();
        tileMap->draw();
        window->onAfterRender();
    }
}

