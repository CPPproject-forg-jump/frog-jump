#include "input.h"
#include "game.h"

extern float frogX;
extern float frogY;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_W:
                frogY += 0.1f;
                break;
            case GLFW_KEY_S:
                frogY -= 0.1f;
                break;
            case GLFW_KEY_A:
                frogX -= 0.1f;
                break;
            case GLFW_KEY_D:
                frogX += 0.1f;
                break;
            case GLFW_KEY_R:
                initGame();
                break;
        }
    }
}
