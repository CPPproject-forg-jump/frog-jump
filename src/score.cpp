//score.cpp
#include "game.h"
#include "input.h"
#include "score.h"

int currentScore = 0;
int highScore = 0;

void increaseScore(int amount) {
    currentScore += 1;
    if (currentScore > highScore) {
        highScore = currentScore;
    }
}

int getCurrentScore() {
    return currentScore;
}

int getHighScore() {
    return highScore;
}

void resetScore() {
    currentScore = 0;
}
