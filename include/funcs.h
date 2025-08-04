#ifndef FUNCS_H
#define FUNCS_H

#include <windows.h>  // For clearing console (Windows)

void saveLeaderboard(const char* filename, const char* name, int score);
void printLeaderboard(const char* filename);

void clearScreen();
const char* getColor(int value);

void initializeBoard(int* board, int size);
void printBoard(int* board, int size, int score, int best);
void addRandomTile(int* board, int size);

int moveRight(int* board, int size, int* score);
int combineRight(int* row, int size, int* score);
int shiftRight(int* row, int size);

int moveLeft(int* board, int size, int* score);
int shiftLeft(int* row, int size);
int combineLeft(int* row, int size, int* score);

int moveUp(int* board, int size, int* score);
int moveDown(int* board, int size, int* score);

int checkLoss(int* board, int size);

int loadHighScore(const char* filename);
void saveHighScore(const char* filename, int score);


#endif // FUNCS_H
