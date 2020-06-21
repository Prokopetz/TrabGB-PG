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
            if (!gameManager->isGameOver) {
                gameManager->onKeyboardClick(Player::NORTH_WEST);
            }
        }
        if (Keyboard::KeyDown(GLFW_KEY_RIGHT) || Keyboard::KeyDown(GLFW_KEY_D)) {
            if (!gameManager->isGameOver) {
                gameManager->onKeyboardClick(Player::NORTH_EAST);
            }
        }
        if (Keyboard::KeyDown(GLFW_KEY_LEFT) || Keyboard::KeyDown(GLFW_KEY_A)) {
            if (!gameManager->isGameOver) {
                gameManager->onKeyboardClick(Player::SOUTH_WEST);
            }
        }
        if (Keyboard::KeyDown(GLFW_KEY_DOWN) || Keyboard::KeyDown(GLFW_KEY_S)) {
            if (!gameManager->isGameOver) {
                gameManager->onKeyboardClick(Player::SOUTH_EAST);
            }
        }
        if (Keyboard::KeyDown(GLFW_KEY_X)) {
            if (gameManager->isGameOver || gameManager->won) {
                gameManager->restartGame();
            }
        }
        gameManager->onGameLoop();
        if (gameManager->won) {
            gameManager->onGameWin();
        }
        else if (!gameManager->isGameOver) {
            gameManager->draw();
        }
        else {
            gameManager->onGameOver();
        }
        window->onAfterRender();
    }
}

