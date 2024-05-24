#include "game.h"
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>

const float FROG_SIZE = 0.05f;
const float LOG_WIDTH = 0.2f;
const float LOG_HEIGHT = 0.1f;
const int NUM_LOGS = 5;
const float SPEED = 0.01f;

float frogX = 0.0f;
float frogY = -0.9f;
bool onLog = false;
float logSpeed = 0.0f;

struct Log {
    float x, y;
    float speed;
};
std::vector<Log> logs;

void initGame() {
    srand(static_cast<unsigned>(time(0)));
    logs.clear();
    for (int i = 0; i < NUM_LOGS; ++i) {
        float y = -0.8f + i * 0.4f;
        float x = (rand() % 200 - 100) / 100.0f;
        float speed = SPEED * (rand() % 3 + 1);
        if (rand() % 2 == 0) speed = -speed;
        logs.push_back({x, y, speed});
    }
    frogX = 0.0f;
    frogY = -0.9f;
    onLog = false;
    logSpeed = 0.0f;
}

void updateGame() {
    for (auto& log : logs) {
        log.x += log.speed;
        if (log.x > 1.0f) log.x = -1.0f;
        if (log.x < -1.0f) log.x = 1.0f;
    }

    onLog = false;
    for (const auto& log : logs) {
        if (frogY >= log.y - LOG_HEIGHT / 2 && frogY <= log.y + LOG_HEIGHT / 2 &&
            frogX >= log.x - LOG_WIDTH / 2 && frogX <= log.x + LOG_WIDTH / 2) {
            onLog = true;
            logSpeed = log.speed;
            break;
        }
    }

    if (onLog) {
        frogX += logSpeed;
    }

    if (frogY > -0.8f && frogY < 0.8f && !onLog) {
        std::cout << "Game Over!" << std::endl;
        initGame();
    }

    if (frogY > 0.8f) {
        std::cout << "You Win!" << std::endl;
        initGame();
    }
}

void renderGame() {
    glClear(GL_COLOR_BUFFER_BIT);

    for (const auto& log : logs) {
        glBegin(GL_QUADS);
        glColor3f(0.55f, 0.27f, 0.07f);
        glVertex2f(log.x - LOG_WIDTH / 2, log.y - LOG_HEIGHT / 2);
        glVertex2f(log.x + LOG_WIDTH / 2, log.y - LOG_HEIGHT / 2);
        glVertex2f(log.x + LOG_WIDTH / 2, log.y + LOG_HEIGHT / 2);
        glVertex2f(log.x - LOG_WIDTH / 2, log.y + LOG_HEIGHT / 2);
        glEnd();
    }

    glBegin(GL_QUADS);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(frogX - FROG_SIZE, frogY - FROG_SIZE);
    glVertex2f(frogX + FROG_SIZE, frogY - FROG_SIZE);
    glVertex2f(frogX + FROG_SIZE, frogY + FROG_SIZE);
    glVertex2f(frogX - FROG_SIZE, frogY + FROG_SIZE);
    glEnd();
}
