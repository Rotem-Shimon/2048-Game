
#ifndef GAME_H
#define GAME_H

void playGame(int* board, int size, int scoreToWin);
char getUserInput();
void printMenu(const char* playerName, int best);
void startNewGame(int* board, int size, int scoreToWin, int* score, int* best);
void updateBestScore(int currentScore, int* bestScore);


#endif // GAME_H
