#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../include/game.h"
#include "../include/funcs.h"


void playGame(int* board, int size, int scoreToWin)
{
    int score = 0;      // Current score
    int best = 0;       // Best score across all games
    char input;         // User input
    int gameStarted = 0; //

    // Display a message if no game has started yet
    printf("\nNeed to start game first\n");

    // Game loop
    while (1) {
        printMenu(); // Display menu options

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
                best = (score > best) ? score : best; // Update best score
                if (score >= scoreToWin) //Check for win
                {
                    printf("You won %d! - Ending game\n", score);
                    break;
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

void printMenu() 
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
}