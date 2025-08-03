
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/funcs.h"

void initializeBoard(int* board, int size) {
	for (int i = 0; i < size * size; ++i) {
		*(board + i) = 0; // Initialize all cells to 0
	}
}

void printBoard(int* board, int size, int score, int best) {
	int width = 6; // Fixed width for each cell, ensures alignment

	// Print current score and best score
	printf("Score: %d   Best: %d\n", score, best);

	for (int row = 0; row < size; ++row) {
		// Print the top border for the current row
		for (int col = 0; col < size; ++col) {
			for (int w = 0; w < width; ++w) {
				printf("-");
			}
		}
		printf("-\n");

		// Print the values of the current row
		printf("|");
		for (int col = 0; col < size; ++col) {
			int value = *(board++); // Access the current value using pointer arithmetic
			if (value == 0) {
				printf("%*s|", width - 1, ""); // Print empty space for 0
			}
			else {
				printf("%*d|", width - 1, value); // Print the value with proper spacing
			}
		}
		printf("\n");
	}

	// Print the bottom border for the last row
	for (int col = 0; col < size; ++col) {
		for (int w = 0; w < width; ++w) {
			printf("-");
		}
	}
	printf("-\n");
}

void addRandomTile(int* board, int size) {
	int emptyCount = 0;

	// Count empty cells
	for (int i = 0; i < size * size; i++) {
		if (*(board + i) == 0) {
			emptyCount++;
		}
	}

	// If no empty cells, exit
	if (emptyCount == 0) {
		return;
	}

	// Select a random empty cell
	int randomIndex = rand() % emptyCount;
	emptyCount = 0;

	// Assign 2 (70%) or 4 (30%) to the selected empty cell
	for (int i = 0; i < size * size; i++) {
		if (*(board + i) == 0) {
			if (emptyCount == randomIndex) {
				*(board + i) = (rand() % 10 < 7) ? 2 : 4;
				break;
			}
			emptyCount++;
		}
	}
}

//moveRight
int moveRight(int* board, int size, int* score) {
	int moved = 0; // Flag to check if any tiles moved

	for (int row = 0; row < size; row++) {
		// Step 1: Calculate the start of the row in the board
		int* rowStart = board + row * size;

		// Step 2: Shift numbers to the right
		int tempMoved = shiftRight((int*)rowStart, size);
		if (tempMoved) {
			moved = 1; // Update moved if any tiles shifted
		}

		// Step 3: Combine adjacent numbers
		tempMoved = combineRight((int*)rowStart, size, score);
		if (tempMoved) {
			moved = 1; // Update moved if any tiles combined
		}

		// Step 4: Shift again to remove gaps
		tempMoved = shiftRight((int*)rowStart, size);
		if (tempMoved) {
			moved = 1; // Update moved if any tiles shifted again
		}
	}

	return moved; // Return whether any tiles were moved
}
int combineRight(int* row, int size, int* score) {
	int moved = 0;

	// Combine adjacent equal numbers
	for (int i = size - 1; i > 0; i--) {
		if (*(row + i) == *(row + i - 1) && *(row + i) != 0) {
			*(row + i) *= 2;       // Combine tiles
			*score += *(row + i);  // Update score
			*(row + i - 1) = 0;    // Clear the combined tile
			moved = 1;
		}
	}

	return moved;
}
int shiftRight(int* row, int size) {
	int moved = 0;

	// Shift numbers to the right
	for (int i = size - 1; i > 0; i--) {
		if (*(row + i) == 0) {
			for (int j = i - 1; j >= 0; j--) {
				if (*(row + j) != 0) {
					*(row + i) = *(row + j);
					*(row + j) = 0;
					moved = 1;
					break;
				}
			}
		}
	}

	return moved;
}

//moveLeft
int moveLeft(int* board, int size, int* score) {
	int moved = 0; // Flag to check if any tiles moved

	for (int row = 0; row < size; row++) {
		// Step 1: Calculate the start of the row in the board
		int* rowStart = board + row * size;

		// Step 2: Shift numbers to the left
		int tempMoved = shiftLeft((int*)rowStart, size);
		if (tempMoved) {
			moved = 1; // Update moved if any tiles shifted
		}

		// Step 3: Combine adjacent numbers
		tempMoved = combineLeft((int*)rowStart, size, score);
		if (tempMoved) {
			moved = 1; // Update moved if any tiles combined
		}

		// Step 4: Shift again to remove gaps
		tempMoved = shiftLeft((int*)rowStart, size);
		if (tempMoved) {
			moved = 1; // Update moved if any tiles shifted again
		}
	}

	return moved; // Return whether any tiles were moved
}
int shiftLeft(int* row, int size) {
	int moved = 0;

	// Shift numbers to the left
	for (int i = 0; i < size - 1; i++) {
		if (*(row + i) == 0) {
			for (int j = i + 1; j < size; j++) {
				if (*(row + j) != 0) {
					*(row + i) = *(row + j);
					*(row + j) = 0;
					moved = 1;
					break;
				}
			}
		}
	}

	return moved;
}
int combineLeft(int* row, int size, int* score) {
	int moved = 0;

	// Combine adjacent equal numbers
	for (int i = 0; i < size - 1; i++) {
		if (*(row + i) == *(row + i + 1) && *(row + i) != 0) {
			*(row + i) *= 2;       // Combine tiles
			*score += *(row + i);  // Update score
			*(row + i + 1) = 0;    // Clear the combined tile
			moved = 1;
		}
	}

	return moved;
}

int moveUp(int* board, int size, int* score) {
	int moved = 0; // Flag to indicate if any tiles were moved

	for (int col = 0; col < size; col++) { // Loop through each column
		// Step 1: Shift numbers upward
		for (int row = 0; row < size - 1; row++) { // Loop from top to bottom
			if (*(board + row * size + col) == 0) { // If the current cell is empty
				for (int k = row + 1; k < size; k++) { // Search for the next non-empty cell below
					if (*(board + k * size + col) != 0) {
						*(board + row * size + col) = *(board + k * size + col); // Move value up
						*(board + k * size + col) = 0; // Clear the source
						moved = 1; // Update move flag
						break;
					}
				}
			}
		}

		// Step 2: Combine numbers upward
		for (int row = 0; row < size - 1; row++) { // Loop from top to bottom
			if (*(board + row * size + col) != 0 && *(board + row * size + col) == *(board + (row + 1) * size + col)) {
				*(board + row * size + col) *= 2; // Combine tiles (double the value)
				*score += *(board + row * size + col); // Update score
				*(board + (row + 1) * size + col) = 0; // Clear the lower tile
				moved = 1; // Update move flag
			}
		}

		// Step 3: Shift numbers upward again
		for (int row = 0; row < size - 1; row++) { // Loop from top to bottom
			if (*(board + row * size + col) == 0) { // If the current cell is empty
				for (int k = row + 1; k < size; k++) { // Search for the next non-empty cell below
					if (*(board + k * size + col) != 0) {
						*(board + row * size + col) = *(board + k * size + col); // Move value up
						*(board + k * size + col) = 0; // Clear the source
						moved = 1; // Update move flag
						break;
					}
				}
			}
		}
	}

	return moved; // Return whether any tiles were moved or merged
}

int moveDown(int* board, int size, int* score) {
	int moved = 0; // Flag to indicate if any tiles were moved

	for (int col = 0; col < size; col++) { // Loop through each column
		// Step 1: Shift numbers downward
		for (int row = size - 1; row > 0; row--) { // Loop from bottom to top
			if (*(board + row * size + col) == 0) { // If the current cell is empty
				for (int k = row - 1; k >= 0; k--) { // Search for the next non-empty cell above
					if (*(board + k * size + col) != 0) {
						*(board + row * size + col) = *(board + k * size + col); // Move value down
						*(board + k * size + col) = 0; // Clear the source
						moved = 1; // Update move flag
						break;
					}
				}
			}
		}

		// Step 2: Combine numbers downward
		for (int row = size - 1; row > 0; row--) { // Loop from bottom to top
			if (*(board + row * size + col) != 0 && *(board + row * size + col) == *(board + (row - 1) * size + col)) {
				*(board + row * size + col) *= 2; // Combine tiles (double the value)
				*score += *(board + row * size + col); // Update score
				*(board + (row - 1) * size + col) = 0; // Clear the upper tile
				moved = 1; // Update move flag
			}
		}

		// Step 3: Shift numbers downward again
		for (int row = size - 1; row > 0; row--) { // Loop from bottom to top
			if (*(board + row * size + col) == 0) { // If the current cell is empty
				for (int k = row - 1; k >= 0; k--) { // Search for the next non-empty cell above
					if (*(board + k * size + col) != 0) {
						*(board + row * size + col) = *(board + k * size + col); // Move value down
						*(board + k * size + col) = 0; // Clear the source
						moved = 1; // Update move flag
						break;
					}
				}
			}
		}
	}

	return moved; // Return whether any tiles were moved or merged
}

int checkLoss(int* board, int size) {
	// Check for empty tiles
	for (int i = 0; i < size * size; i++) {
		if (*(board + i) == 0) {
			return 0; // Game is not over
		}
	}

	// Check for possible moves
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			int current = *(board + row * size + col);

			// Check the tile to the right (only if not in the last column)
			if (col < size - 1) {
				int right = *(board + row * size + (col + 1));
				if (current == right) {
					return 0; // Game is not over
				}
			}

			// Check the tile below (only if not in the last row)
			if (row < size - 1) {
				int below = *(board + (row + 1) * size + col);
				if (current == below) {
					return 0; // Game is not over
				}
			}
		}
	}
	// If no empty tiles and no valid moves exist
	return 1; // Game is over
}

// Load high score from file, return 0 if file doesn't exist
int loadHighScore(const char* filename) {
	FILE* file = fopen(filename, "r");
	if (!file) return 0;  // No file yet
	int highScore;
	fscanf(file, "%d", &highScore);
	fclose(file);
	return highScore;
}

// Save high score to file
void saveHighScore(const char* filename, int score) {
	FILE* file = fopen(filename, "w");
	if (!file) return;
	fprintf(file, "%d", score);
	fclose(file);
}
