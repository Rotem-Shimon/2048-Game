#define HIGHSCORE_FILE "highscore.txt"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "../include/game.h"
#include "../include/funcs.h"


void playGame(int* board, int size, int scoreToWin) {
    const char* leaderboardFile = "leaderboard.txt";
    int score = 0;
    int best = loadHighScore("highscore.txt");
    char playerName[50];
    printf("Enter your name: ");
    scanf("%49s", playerName);

    while (1) {
        printf("\n==== 2048 Menu ====\n");
        printf("1. Start Game\n");
        printf("2. View Leaderboard\n");
        printf("3. Exit\n");
        printf("Choose an option: ");
        int choice;
        scanf("%d", &choice);

        if (choice == 1) {
            startNewGame(board, size, scoreToWin, &score, &best);
            while (1) {
                char input = getUserInput();
                int moveMade = 0;
                switch (input) {
                case 'r': moveMade = moveRight(board, size, &score); break;
                case 'l': moveMade = moveLeft(board, size, &score); break;
                case 'u': moveMade = moveUp(board, size, &score); break;
                case 'd': moveMade = moveDown(board, size, &score); break;
                case 'e':
                    printf("\nGame Over! Your score: %d\n", score);
                    moveMade = -1;
                    break;
                }
                if (moveMade == -1) break;
                if (moveMade) {
                    if (score > best) {
                        best = score;
                        saveHighScore("highscore.txt", best);
                    }
                    addRandomTile(board, size);
                    updateBestScore(score, &best);
                    printBoard(board, size, score, best);
                    if (checkLoss(board, size)) {
                        printf("\nGame Over! Your score: %d\n", score);
                        break;
                    }
                }
                else {
                    printf("\nNo tiles moved. Try another direction.\n");
                }
            }
            // Save only once after the game ends
            saveLeaderboard(leaderboardFile, playerName, score);
        }
        else if (choice == 2) {
            printLeaderboard(leaderboardFile);
        }
        else if (choice == 3) {
            printf("Goodbye!\n");
            break;
        }
        else {
            printf("Invalid choice. Try again.\n");
        }
    }
}

char getUserInput() 
{
    char input;
    do {
        scanf("%c", &input);
    } while (isspace(input));
    return tolower(input);
}

void startNewGame(int* board, int size, int scoreToWin, int* score, int* best)
{
    printf("\n----- STARTING A GAME -----\n");
    printf("Score for a win: %d\n\n", scoreToWin);
    initializeBoard((int*)board, size);
    addRandomTile((int*)board, size);
    addRandomTile((int*)board, size);
    printBoard((int*)board, size, 0, *best); // Display board
}

void updateBestScore(int currentScore, int* bestScore) 
{
    if (currentScore > *bestScore) {
        *bestScore = currentScore;
    }
}

void printMenu(const char* playerName, int best)
{
    printf("\nPlease choose one of the following options:\n");
    printf("N/n - New Game\n");
    printf("R/r - Move Right\n");
    printf("L/l - Move Left\n");
    printf("U/u - Move Up\n");
    printf("D/d - Move Down\n");
    printf("E/e - Exit\n");
    printf("\nEnter your move: ");
    printf("\n");
    printf("Best Score: %d\n", best);
}