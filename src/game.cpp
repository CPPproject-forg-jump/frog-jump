#include "game.h"
#include "score.h"
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <ctime>
#include <iostream>

const float FROG_SIZE = 0.05f;
const float LOG_WIDTH = 0.2f;
const float LOG_HEIGHT = 0.1f;
const int NUM_LOGS = 5;
const float LOG_SPEED = 0.005f;
const int NUM_CARS = 5;
const float CAR_WIDTH = 0.15f;
const float CAR_HEIGHT = 0.1f;
const float CAR_SPEED = 0.01f;

float frogX = 0.0f;
float frogY = -0.9f;
bool onLog = false;
float logSpeed = 0.0f;

std::vector<Log> logs;
std::vector<Car> cars;

bool isMovingLeft = true;
bool isRiver = true;
bool gameRunning = false;
bool menuRunning = true;

void renderLogs() {
    for (const auto& log : logs) {
        glBegin(GL_QUADS);
        glColor3f(0.55f, 0.27f, 0.07f);
        glVertex2f(log.x - LOG_WIDTH / 2, log.y - LOG_HEIGHT / 2);
        glVertex2f(log.x + LOG_WIDTH / 2, log.y - LOG_HEIGHT / 2);
        glVertex2f(log.x + LOG_WIDTH / 2, log.y + LOG_HEIGHT / 2);
        glVertex2f(log.x - LOG_WIDTH / 2, log.y + LOG_HEIGHT / 2);
        glEnd();
    }
}

void renderCars() {
    for (const auto& car : cars) {
        glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0f); // 修改顏色為紅色，表示車子
        glVertex2f(car.x - CAR_WIDTH / 2, car.y - CAR_HEIGHT / 2);
        glVertex2f(car.x + CAR_WIDTH / 2, car.y - CAR_HEIGHT / 2);
        glVertex2f(car.x + CAR_WIDTH / 2, car.y + CAR_HEIGHT / 2);
        glVertex2f(car.x - CAR_WIDTH / 2, car.y + CAR_HEIGHT / 2);
        glEnd();
    }
}

void initGame() {
    srand(static_cast<unsigned>(time(0)));
    
    logs.clear();
    for (int i = 0; i < NUM_LOGS; ++i) {
        float y = -0.8f + i * (LOG_HEIGHT + 0.02f);
        float x = (isMovingLeft) ? -1.0f + LOG_WIDTH / 2 : 1.0f - LOG_WIDTH / 2;
        float speed = LOG_SPEED * (rand() % 3 + 1);
        if (!isMovingLeft) speed = -speed;
        logs.push_back({x, y, speed});
        isMovingLeft = !isMovingLeft;
    }

    cars.clear();
    for (int i = 0; i < NUM_CARS; ++i) {
        float y = -0.2f + i * (CAR_HEIGHT + 0.02f);
        float x = (isMovingLeft) ? 1.0f - CAR_WIDTH / 10 : -1.0f + CAR_WIDTH / 10;
        float speed = CAR_SPEED * (rand() % 3 + 1);
        if (!isMovingLeft) speed = -speed;
        cars.push_back({x, y, speed});
        isMovingLeft = !isMovingLeft;
    }

    frogX = 0.0f;
    frogY = -0.9f;
    onLog = false;
    logSpeed = 0.0f;
    gameRunning = true;
    resetScore();
}

void updateLogs() {
    for (auto& log : logs) {
        log.x += log.speed;
        if (log.x > 1.0f) log.x = -1.0f;
        if (log.x < -1.0f) log.x = 1.0f;
    }
}

void updateCars() {
    for (auto& car : cars) {
        car.x += car.speed;
        if (car.x > 1.0f && car.speed > 0) car.x = -1.0f - CAR_WIDTH / 2;
        if (car.x < -1.0f - CAR_WIDTH / 2 && car.speed < 0) car.x = 1.0f;
    }
}

void updateGame() {
    if (!gameRunning) return;

    updateLogs();
    updateCars();

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

    for (const auto& car : cars) {
        if (frogY >= car.y - CAR_HEIGHT / 2 && frogY <= car.y + CAR_HEIGHT / 2 &&
            frogX >= car.x - CAR_WIDTH / 2 && frogX <= car.x + CAR_WIDTH / 2) {
            std::cout << "Game Over!" << std::endl;
            std::cout << "Current Score: " << getCurrentScore() << std::endl;
            std::cout << "High Score: " << getHighScore() << std::endl;
            gameRunning = false;
        }
    }

    if (frogY > -0.8f && frogY < -0.3f && !onLog) {
        std::cout << "Game Over!" << std::endl;
        std::cout << "Current Score: " << getCurrentScore() << std::endl;
        std::cout << "High Score: " << getHighScore() << std::endl;
        gameRunning = false;
    }

    if (frogY > 0.6f) {
        frogX = 0.0f; // 重置玩家位置
        frogY = -0.9f;
        increaseScore(10); // 過河獲得額外分數
    }
}

void renderGame() {
    glClear(GL_COLOR_BUFFER_BIT);

    renderLogs();
    renderCars();

    glBegin(GL_QUADS);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(frogX - FROG_SIZE, frogY - FROG_SIZE);
    glVertex2f(frogX + FROG_SIZE, frogY - FROG_SIZE);
    glVertex2f(frogX + FROG_SIZE, frogY + FROG_SIZE);
    glVertex2f(frogX - FROG_SIZE, frogY + FROG_SIZE);
    glEnd();
}
