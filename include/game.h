
#ifndef GAME_H
#define GAME_H

void playGame(int* board, int size, int scoreToWin);
char getUserInput();
void printMenu();
void startNewGame(int* board, int size, int scoreToWin, int* score, int* best);
void updateBestScore(int currentScore, int* bestScore);


#endif // GAME_H
