
#ifndef FUNCS_H
#define FUNCS_H

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

#endif // FUNCS_H
