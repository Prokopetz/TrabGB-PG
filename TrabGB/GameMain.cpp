#include <iostream>
#include "Tile.h"
#include "Window.h"
#include "GameManager.h"
#include "Player.h"

//NOMES: JOAO DACOL SOARES E NICOLAS GRISA PROKOPETZ
int main() {
    Window* window = new Window();

    GameManager* gameManager = new GameManager();

    while (!window->shouldCloseProgram()) {
        window->onBeforeRender();
        if (Mouse::ButtonUp(0)) {
            gameManager->onMouseClick(Mouse::GetMouseX(), Mouse::GetMouseY());
        }
        if (Keyboard::KeyDown(GLFW_KEY_W) || Keyboard::KeyDown(GLFW_KEY_UP)) {
            gameManager->onKeyboardClick(Player::NORTH_WEST);
        }
        if (Keyboard::KeyDown(GLFW_KEY_RIGHT) || Keyboard::KeyDown(GLFW_KEY_D)) {
            gameManager->onKeyboardClick(Player::NORTH_EAST);
        }
        if (Keyboard::KeyDown(GLFW_KEY_LEFT) || Keyboard::KeyDown(GLFW_KEY_A)) {
            gameManager->onKeyboardClick(Player::SOUTH_WEST);
        }
        if (Keyboard::KeyDown(GLFW_KEY_DOWN) || Keyboard::KeyDown(GLFW_KEY_S)) {
            gameManager->onKeyboardClick(Player::SOUTH_EAST);
        }
        gameManager->onGameLoop();
        if (gameManager->won) {
            
        }
        else if (!gameManager->isGameOver) {
            gameManager->draw();
        }
        window->onAfterRender();
    }
}

