#include <GLFW/glfw3.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>

// Constants
const int WIDTH = 800;
const int HEIGHT = 600;
const float FROG_SIZE = 0.05f;
const float LOG_WIDTH = 0.2f;
const float LOG_HEIGHT = 0.1f;
const int NUM_LOGS = 5;
const float SPEED = 0.01f;

// Game variables
float frogX = 0.0f;
float frogY = -0.9f;
bool onLog = false;
float logSpeed = 0.0f;

struct Log {
    float x, y;
    float speed;
};
std::vector<Log> logs;

// Function prototypes
void initGame();
void updateGame();
void renderGame();
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

// Initialize game
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

// Update game state
void updateGame() {
    for (auto& log : logs) {
        log.x += log.speed;
        if (log.x > 1.0f) log.x = -1.0f;
        if (log.x < -1.0f) log.x = 1.0f;
    }

    // Check collision and update frog position if on log
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

    // Check if frog falls into water
    if (frogY > -0.8f && frogY < 0.8f && !onLog) {
        std::cout << "Game Over!" << std::endl;
        initGame();
    }

    // Check if frog reaches the top
    if (frogY > 0.8f) {
        std::cout << "You Win!" << std::endl;
        initGame();
    }
}

// Render game state
void renderGame() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw logs
    for (const auto& log : logs) {
        glBegin(GL_QUADS);
        glColor3f(0.55f, 0.27f, 0.07f); // Brown color
        glVertex2f(log.x - LOG_WIDTH / 2, log.y - LOG_HEIGHT / 2);
        glVertex2f(log.x + LOG_WIDTH / 2, log.y - LOG_HEIGHT / 2);
        glVertex2f(log.x + LOG_WIDTH / 2, log.y + LOG_HEIGHT / 2);
        glVertex2f(log.x - LOG_WIDTH / 2, log.y + LOG_HEIGHT / 2);
        glEnd();
    }

    // Draw frog
    glBegin(GL_QUADS);
    glColor3f(0.0f, 1.0f, 0.0f); // Green color
    glVertex2f(frogX - FROG_SIZE, frogY - FROG_SIZE);
    glVertex2f(frogX + FROG_SIZE, frogY - FROG_SIZE);
    glVertex2f(frogX + FROG_SIZE, frogY + FROG_SIZE);
    glVertex2f(frogX - FROG_SIZE, frogY + FROG_SIZE);
    glEnd();
}

// Key callback
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
        renderGame();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
