#ifndef SCORE_H
#define SCORE_H

extern int currentScore;
extern int highScore;

void increaseScore(int amount);
int getCurrentScore();
int getHighScore();
void resetScore();

#endif // SCORE_H
