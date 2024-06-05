#include "menu.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

bool menuRunning = true;

void renderText(float x, float y, const std::string& text) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, 800, 0, 600, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2f(x, y);
    glColor3f(1.0f, 1.0f, 1.0f); // Set text color to white
    for (const char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

// Function to display the menu
void displayMenu() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Display menu text
    renderText(100, 400, "Press ENTER to Start");
    renderText(100, 300, "Press Q to Quit");

    glfwSwapBuffers(glfwGetCurrentContext());
}

// Function to handle menu input
void handleMenuInput(int key) {
    if (key == GLFW_KEY_ENTER) {
        menuRunning = false;
    } else if (key == GLFW_KEY_Q) {
        glfwSetWindowShouldClose(glfwGetCurrentContext(), GLFW_TRUE);
    }
}
