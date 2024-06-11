#include <GLFW/glfw3.h>
#include "game.h"
#include "input.h"
#include "score.h"
#include "menu.h"
#include <iostream>

const int WIDTH = 800;
const int HEIGHT = 400;

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Frogger Game", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, keyCallback);

    while (!glfwWindowShouldClose(window)) {
        if (menuRunning) {
            renderMenu();
            renderStartButton();
        } else if (gameRunning) {
            updateGame();
            renderGame();
        } else {
            renderMenu();
            renderStartButton();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
