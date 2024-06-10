//game.h
#ifndef GAME_H
#define GAME_H
#include <vector>

struct Log {
    float x, y;
    float speed;
};
struct Car {
    float x, y;
    float speed;
};

extern bool gameRunning;

void initGame();
void updateGame();
void renderGame();

#endif // GAME_H