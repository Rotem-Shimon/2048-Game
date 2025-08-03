#define HIGHSCORE_FILE "highscore.txt"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "../include/game.h"
#include "../include/funcs.h"


void playGame(int* board, int size, int scoreToWin)
{
    int score = 0;      // Current score
    char playerName[50];
    printf("Enter your name: ");
    scanf("%49s", playerName);

    char highScoreFile[150];
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    sprintf(highScoreFile, "highscore_%s_%04d%02d%02d_%02d%02d%02d.txt",
        playerName,
        t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
        t->tm_hour, t->tm_min, t->tm_sec);

    int best = loadHighScore(highScoreFile);
    char input;         // User input
    int gameStarted = 0; //

    // Display a message if no game has started yet
    printf("\nNeed to start game first\n");

    // Game loop
    while (1) {
        printMenu(playerName, best); // Display menu options

        input = getUserInput(); // Get user input

        // Handle user input
        if (input == 'n') {
            gameStarted = 1;
            startNewGame((int*)board, size, scoreToWin, &score, &best); // new game
        }
        else if (input == 'e') {
            // Exit the game
            if (!gameStarted) // If the user tries to exit without starting a game
            {
                printf("\nNeed to start a game first.\n");
                continue;
            }
            printf("\n----- Ending previous game -----\n");
            printf("Your score: %d  Best score: %d\n", score, best);
            printf("Bye bye\n");
            updateBestScore(score, &best);
            break;
        }
        else if (input == 'r' || input == 'l' || input == 'u' || input == 'd') {
            // Handle moves
            if (!gameStarted) // If the user tries to exit without starting a game
            {
                printf("\nNeed to start a game first.\n");
                continue;
            }
            int moveMade = 0; // Track if a move was made
            switch (input) {
            case 'r':
                moveMade = moveRight((int*)board, size, &score);
                break;
            case 'l':
                moveMade = moveLeft((int*)board, size, &score);
                break;
            case 'u':
                moveMade = moveUp((int*)board, size, &score);
                break;
            case 'd':
                moveMade = moveDown((int*)board, size, &score);
                break;
            }

            if (moveMade) {
                if (score > best) {
                    best = score;
                    saveHighScore(highScoreFile, best); // Save to file
                }

                if (score >= scoreToWin) //Check for win
                {
                    printf("You reached %d! Do you want to keep playing? (y/n): ", scoreToWin);
                    char choice;
                    scanf(" %c", &choice);
                    if (tolower(choice) == 'n') {
                        printf("Ending game.\n");
                        break;
                    }
                }
                addRandomTile((int*)board, size); // Add a new random tile
                updateBestScore(score, &best);
                printBoard((int*)board, size, score, best); // Display board
                //Check for loss
                int resLoss = checkLoss((int*)board, size);
                if (resLoss)
                {
                    printf("Game over your score is %d\n", score);
                    break;
                }
            }
            else {
                printf("\nNo tiles moved. Try a different direction.\n");
            }
        }
        else {
            // Invalid input
            if (!gameStarted) // If the user tries to exit without starting a game
            {
                printf("\nNeed to start a game first.\n");
                continue;
            }
            printf("\nInvalid input. Please try again.\n");
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