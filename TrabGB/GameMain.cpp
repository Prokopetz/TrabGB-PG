#include <iostream>
#include "Tile.h"
#include "Window.h"
#include "TileMap.h"

//NOMES: JOAO DACOL SOARES E NICOLAS GRISA PROKOPETZ
int main() {
    Window* window = new Window();

    TileMap* tileMap = new TileMap();

    while (!window->shouldCloseProgram()) {
        window->onBeforeRender();
        if (Mouse::ButtonUp(0)) {
            tileMap->onMouseClick(Mouse::GetMouseX(), Mouse::GetMouseY());
        }
        if (Keyboard::KeyDown(GLFW_KEY_W) || Keyboard::KeyDown(GLFW_KEY_UP)) {
            tileMap->onKeyboardClick(7);
        }
        if (Keyboard::KeyDown(GLFW_KEY_RIGHT) || Keyboard::KeyDown(GLFW_KEY_D)) {
            tileMap->onKeyboardClick(5);
        }
        if (Keyboard::KeyDown(GLFW_KEY_LEFT) || Keyboard::KeyDown(GLFW_KEY_A)) {
            tileMap->onKeyboardClick(8);
        }
        if (Keyboard::KeyDown(GLFW_KEY_DOWN) || Keyboard::KeyDown(GLFW_KEY_S)) {
            tileMap->onKeyboardClick(6);
        }
        tileMap->draw();
        window->onAfterRender();
    }
}

