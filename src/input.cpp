//input.cpp
#include "input.h"
#include "game.h"
#include "score.h"
#include "menu.h"

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (menuRunning) {
            if (key == GLFW_KEY_R) {
                menuRunning = false;
                initGame();
                gameRunning = true;
            }
        } else if (gameRunning) {
            switch (key) {
                case GLFW_KEY_W:
                    frogY += 0.12f;
                    increaseScore(1);
                break;
                case GLFW_KEY_S:
                    frogY -= 0.12f;
                    break;
                case GLFW_KEY_A:
                    frogX -= 0.12f;
                    break;
                case GLFW_KEY_D:
                    frogX += 0.12f;
                    break;
                case GLFW_KEY_R:
                    if (!gameRunning) {
                        initGame();
                        gameRunning = true;
                    }
                    break;
                default:
                    break;
            }
        } else {
            if (key == GLFW_KEY_R) {
                initGame();
                gameRunning = true;
            }
        }
    }
}