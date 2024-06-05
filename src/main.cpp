#include <GLFW/glfw3.h>
#include "game.h"
#include "input.h"
#include "score.h"
#include "menu.h"
#include<iostream>

const int WIDTH = 800;
const int HEIGHT = 600;

float frogY_last = -0.9f;

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
    initGame();

    while (!glfwWindowShouldClose(window)) {
        updateGame();
        if (frogY > frogY_last) {
            increaseScore(1);
        }

        renderGame();
        std::cout << "Current Score: " << getCurrentScore() << " | High Score: " << getHighScore() << std::endl;

        if (!gameRunning) {
            std::cout << "Press R to Restart" << std::endl;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}