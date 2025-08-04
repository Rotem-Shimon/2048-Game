#define MAX_ENTRIES 10

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/funcs.h"

typedef struct {
	char name[50];
	int score;
	char date[20];
} Entry;

// Clear console screen
void clearScreen() {
	system("cls"); // Windows
	// system("clear"); // Uncomment for Linux/Mac
}

// Get color based on tile value
const char* getColor(int value) {
	switch (value) {
	case 2: return "\033[1;37m";   // White
	case 4: return "\033[1;36m";   // Cyan
	case 8: return "\033[1;34m";   // Blue
	case 16: return "\033[1;32m";  // Green
	case 32: return "\033[1;33m";  // Yellow
	case 64: return "\033[1;31m";  // Red
	case 128: return "\033[0;35m"; // Magenta
	case 256: return "\033[0;36m"; // Dark Cyan
	case 512: return "\033[0;34m"; // Dark Blue
	case 1024: return "\033[0;32m";// Dark Green
	case 2048: return "\033[1;33m";// Gold
	default: return "\033[1;35m";  // Purple for >2048
	}
}

void initializeBoard(int* board, int size) {
	for (int i = 0; i < size * size; ++i) {
		*(board + i) = 0; // Initialize all cells to 0
	}
}

void printBoard(int* board, int size, int score, int best) {
	clearScreen();
	printf("Score: %d   Best: %d\n\n", score, best);

	// Top border
	printf("+-------+-------+-------+-------+\n");
	for (int row = 0; row < size; ++row) {
		printf("|");
		for (int col = 0; col < size; ++col) {
			int value = *(board + row * size + col);
			if (value == 0)
				printf("       |");
			else
				printf(" %s%-5d\033[0m |", getColor(value), value);
		}
		printf("\n+-------+-------+-------+-------+\n");
	}
	printf("\nControls: R=Right | L=Left | U=Up | D=Down | E=Exit\n"); // Short instructions under the board 
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

void saveLeaderboard(const char* filename, const char* name, int score) {
	Entry entries[MAX_ENTRIES];
	int count = 0;

	FILE* file = fopen(filename, "r");
	if (file) {
		while (fscanf(file, "%49s %d %19s", entries[count].name, &entries[count].score, entries[count].date) == 3) {
			count++;
			if (count >= MAX_ENTRIES) break;
		}
		fclose(file);
	}

	// Get current date
	time_t now = time(NULL);
	struct tm* t = localtime(&now);
	char date[20];
	strftime(date, sizeof(date), "%Y-%m-%d", t);

	// Add new entry
	if (count < MAX_ENTRIES) {
		strcpy(entries[count].name, name);
		entries[count].score = score;
		strcpy(entries[count].date, date);
		count++;
	}
	else {
		// Replace lowest score if higher
		int minIndex = 0;
		for (int i = 1; i < MAX_ENTRIES; i++) {
			if (entries[i].score < entries[minIndex].score) minIndex = i;
		}
		if (score > entries[minIndex].score) {
			strcpy(entries[minIndex].name, name);
			entries[minIndex].score = score;
			strcpy(entries[minIndex].date, date);
		}
	}

	// Sort by score
	for (int i = 0; i < count - 1; i++) {
		for (int j = i + 1; j < count; j++) {
			if (entries[j].score > entries[i].score) {
				Entry temp = entries[i];
				entries[i] = entries[j];
				entries[j] = temp;
			}
		}
	}

	// Write back
	file = fopen(filename, "w");
	if (!file) return;
	for (int i = 0; i < count && i < MAX_ENTRIES; i++) {
		fprintf(file, "%s %d %s\n", entries[i].name, entries[i].score, entries[i].date);
	}
	fclose(file);
}

void printLeaderboard(const char* filename) {
	Entry entry;
	FILE* file = fopen(filename, "r");
	if (!file) {
		printf("\nNo leaderboard data yet.\n");
		return;
	}

	printf("\n==== Leaderboard ====\n");
	printf("%-15s %-10s %-12s\n", "Name", "Score", "Date");
	printf("-------------------------------\n");
	while (fscanf(file, "%49s %d %19s", entry.name, &entry.score, entry.date) == 3) {
		printf("%-15s %-10d %-12s\n", entry.name, entry.score, entry.date);
	}
	fclose(file);
}
