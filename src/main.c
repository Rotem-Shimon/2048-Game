#include <stdio.h>
#include <stdlib.h>
#include "../include/game.h"
#include "../include/funcs.h"


int main() {
    system("chcp 65001 > nul"); // Force console to UTF-8

    int size = 4; // default board size
    int scoreToWin = 2048; // default goal
    int board[6][6] = {0}; // support up to 6x6 board

    printf("Welcome to 2048!\n");
    playGame((int*)board, size, scoreToWin);

    return 0;
}
