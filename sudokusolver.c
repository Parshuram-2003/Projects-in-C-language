#include <stdio.h>
#include <stdbool.h>

#define N 9

// Function to print the Sudoku board
void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++)
            printf("%2d", grid[row][col]);
        printf("\n");
    }
}

// Function to check if it's safe to place a number in the given cell
bool isSafe(int grid[N][N], int row, int col, int num) {
    // Check if the number is already in the row
    for (int x = 0; x < N; x++)
        if (grid[row][x] == num)
            return false;

    // Check if the number is already in the column
    for (int x = 0; x < N; x++)
        if (grid[x][col] == num)
            return false;

    // Check if the number is already in the 3x3 box
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return false;

    return true;
}

// Function to find an empty cell in the Sudoku grid
bool findEmptyLocation(int grid[N][N], int *row, int *col) {
    for (*row = 0; *row < N; (*row)++)
        for (*col = 0; *col < N; (*col)++)
            if (grid[*row][*col] == 0)
                return true;
    return false;
}

// Function to solve the Sudoku using backtracking
bool solveSudoku(int grid[N][N]) {
    int row, col;

    // If there's no empty cell left, the Sudoku is solved
    if (!findEmptyLocation(grid, &row, &col))
        return true;

    // Try numbers from 1 to 9 in the current empty cell
    for (int num = 1; num <= 9; num++) {
        // Check if it's safe to place the number in the cell
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            // Recursively try to solve the rest of the grid
            if (solveSudoku(grid))
                return true;

            // If placing num in grid[row][col] doesn't lead to a solution, undo the move
            grid[row][col] = 0;
        }
    }

    // If no number from 1 to 9 works, return false (trigger backtracking)
    return false;
}

// Function to take user input for the Sudoku grid
void inputGrid(int grid[N][N]) {
    printf("Enter the Sudoku grid (0 for empty cells):\n");
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            scanf("%d", &grid[row][col]);
        }
    }
}

int main() {
    int grid[N][N];

    inputGrid(grid);

    if (solveSudoku(grid) == true)
        printGrid(grid);
    else
        printf("No solution exists");

    return 0;
}