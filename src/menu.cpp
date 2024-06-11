//menu.cpp
#include "menu.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

void renderMenu() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // 设置清除颜色为绿色
    glClear(GL_COLOR_BUFFER_BIT); // 清除颜色缓冲区

    // 绘制绿色背景
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glEnd();
}

void renderStartButton() {
    // 绘制开始按钮（矩形）
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.5f, 0.5f); // 灰色
    glVertex2f(-0.3f, -0.1f);
    glVertex2f(0.3f, -0.1f);
    glVertex2f(0.3f, 0.1f);
    glVertex2f(-0.3f, 0.1f);
    glEnd();
}

