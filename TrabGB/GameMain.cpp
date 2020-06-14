#include <iostream>
#include "Tile.h"
#include "Window.h"
#include "TileMap.h"
#include "Player.h"

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
            tileMap->onKeyboardClick(Player::NORTH_WEST);
        }
        if (Keyboard::KeyDown(GLFW_KEY_RIGHT) || Keyboard::KeyDown(GLFW_KEY_D)) {
            tileMap->onKeyboardClick(Player::NORTH_EAST);
        }
        if (Keyboard::KeyDown(GLFW_KEY_LEFT) || Keyboard::KeyDown(GLFW_KEY_A)) {
            tileMap->onKeyboardClick(Player::SOUTH_WEST);
        }
        if (Keyboard::KeyDown(GLFW_KEY_DOWN) || Keyboard::KeyDown(GLFW_KEY_S)) {
            tileMap->onKeyboardClick(Player::SOUTH_EAST);
        }
        tileMap->draw();
        window->onAfterRender();
    }
}

