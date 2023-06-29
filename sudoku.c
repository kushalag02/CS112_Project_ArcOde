#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 9

// Function to find the next empty cell in the grid
bool findEmptyCell(int grid[SIZE][SIZE], int* row, int* col) {
    for (*row = 0; *row < SIZE; (*row)++) {
        for (*col = 0; *col < SIZE; (*col)++) {
            if (grid[*row][*col] == 0) {
                return true; // Found an empty cell
            }
        }
    }
    return false; // No empty cell found
}

// Function to check if it is safe to place a number in a particular cell
bool isSafe(int grid[SIZE][SIZE], int row, int col, int num) {
    // Check if the number already exists in the row
    for (int i = 0; i < SIZE; i++) {
        if (grid[row][i] == num) {
            return false; // Number already exists in the row
        }
    }

    // Check if the number already exists in the column
    for (int i = 0; i < SIZE; i++) {
        if (grid[i][col] == num) {
            return false; // Number already exists in the column
        }
    }

    // Check if the number already exists in the 3x3 box
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return false; // Number already exists in the box
            }
        }
    }

    return true; // It is safe to place the number in the cell
}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(int grid[SIZE][SIZE]) {
    int row, col;

    // Find the next empty cell in the grid
    if (!findEmptyCell(grid, &row, &col)) {
        return true; // All cells are filled, puzzle solved
    }

    // Generate a random order of numbers to try
    int numbers[SIZE];
    for (int i = 0; i < SIZE; i++) {
        numbers[i] = i + 1;
    }

    // Shuffle the numbers array
    for (int i = SIZE - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = numbers[i];
        numbers[i] = numbers[j];
        numbers[j] = temp;
    }

    // Try each number in the shuffled order
    for (int i = 0; i < SIZE; i++) {
        int num = numbers[i];
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num; // Place the number in the cell

            if (solveSudoku(grid)) {
                return true; // Number leads to a solution
            }

            grid[row][col] = 0; // Number doesn't lead to a solution, backtrack
        }
    }

    return false; // Backtrack to previous cell
}

// Function to display the Sudoku grid
void displayGrid(int grid[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (col % 3 == 0) {
                printf(" |");
            }
            if (grid[row][col] == 0) {
                printf(" .");
            } else {
                printf(" %d", grid[row][col]);
            }
        }
        printf(" |\n");
        if ((row + 1) % 3 == 0 && row != SIZE - 1) {
            printf("  ------- ------- -------\n");
        }
    }
}


// Function to generate an unsolved Sudoku puzzle
void generatePuzzle(int grid[SIZE][SIZE]) {
    srand(time(NULL));

    // Clear the grid
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            grid[row][col] = 0;
        }
    }

    // Solve the Sudoku puzzle to get a complete solution
    solveSudoku(grid);

    // Remove random entries to create an unsolved puzzle
    int entriesToRemove = 40; // Adjust the number of entries to remove to control the difficulty level

    while (entriesToRemove > 0) {
        int row = rand() % SIZE;
        int col = rand() % SIZE;

        if (grid[row][col] != 0) {
            grid[row][col] = 0;
            entriesToRemove--;
        }
    }
}

// Function to check if the entered number in a cell leads to a valid solution
bool checkSolution(int grid[SIZE][SIZE], int row, int col, int num) {
    // Create a temporary copy of the grid
    int tempGrid[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            tempGrid[i][j] = grid[i][j];
        }
    }

    // Place the entered number in the specified cell
    tempGrid[row][col] = num;

    // Check if the temporary grid can be solved
    return solveSudoku(tempGrid);
}

// Function to print the result of the user's input (correct or wrong)
void printResult(bool isCorrect) {
    if (isCorrect) {
        printf("Correct entry!\n");
    } else {
        printf("Wrong entry!\n");
    }
}

// Function to play the Sudoku game
void playSudoku(int grid[SIZE][SIZE]) {
    while (true) {
        printf("\nSudoku Puzzle:\n");
        displayGrid(grid);
        printf("\nEnter the row, column, and entry (space-separated) or '0 0 0' to exit: ");

        int row, col, entry;
        scanf("%d %d %d", &row, &col, &entry);

        if (row == 0 && col == 0 && entry == 0) {
            // User wants to exit the game and see the solved puzzle
            printf("\nSolved Puzzle:\n");
            int solvedGrid[SIZE][SIZE];
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    solvedGrid[i][j] = grid[i][j];
                }
            }
            solveSudoku(solvedGrid);
            displayGrid(solvedGrid);
            break; // Exit the game
        }

        if (row >= 1 && row <= SIZE && col >= 1 && col <= SIZE && entry >= 1 && entry <= SIZE) {
            row--;
            col--;

            if (grid[row][col] == 0) {
                // Cell is empty, user can enter a number
                if (checkSolution(grid, row, col, entry)) {
                    // Entered number is correct
                    grid[row][col] = entry;
                    printResult(true);
                } else {
                    // Entered number is wrong
                    printResult(false);
                }
            } else {
                // Cell is already filled
                printf("Cell is already filled!\n");
            }
        } else {
            // Invalid input
            printf("Invalid input!\n");
        }
    }
}

int main() {
    int grid[SIZE][SIZE];

    printf("Welcome to Sudoku!\n\n");

    generatePuzzle(grid); // Generate an unsolved Sudoku puzzle

    printf("Unsolved Puzzle:\n");
    displayGrid(grid);

    printf("\nLet's play!\n");
    playSudoku(grid);

    return 0;
}