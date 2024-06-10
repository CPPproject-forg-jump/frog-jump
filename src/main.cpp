//main.cpp
#include <GLFW/glfw3.h>
#include "game.h"
#include "input.h"
#include "score.h"
#include "menu.h"
#include<iostream>

const int WIDTH = 800;
const int HEIGHT = 400;

float frogY_last = -0.9f;
bool menuRunning = true;

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

    while (frogY > frogY_last && frogX == frogX) {
        increaseScore(1);
        if (!gameRunning) {
            //std::cout << "Press R to Restart" << std::endl;
            //std::cout << "Current Score: " << getCurrentScore() << " | High Score: " << getHighScore() << std::endl;
            resetScore();
            break;
        }
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}