#include <iostream>
#include "Tile.h"
#include "Window.h"

int main() {
    Window* window = new Window();

    Tile* tiles[5][5];
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {

            float x = j * 64 + i * 32;

            float y = i * 16;

            tiles[i][j] = new Tile(32.0, 64, x, y);
        }
    }

    while (!window->shouldCloseProgram()) {
        window->onBeforeRender();
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                tiles[i][j]->draw();
            }
        }
        window->onAfterRender();
    }
}

