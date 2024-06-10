//input.h
#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>

extern float frogX;
extern float frogY;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

#endif // INPUT_H