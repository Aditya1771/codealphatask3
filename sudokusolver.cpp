#include <iostream>
#include <vector>

using namespace std;

// Size of the Sudoku grid
const int N = 9;

// Function to print the Sudoku grid
void printGrid(const vector<vector<int>>& grid) {
    for (const auto& row : grid) {
        for (int num : row) {
            cout << num << " ";
        }
        cout << endl;
    }
}

// Function to check if a number can be placed in a given position
bool isSafe(const vector<vector<int>>& grid, int row, int col, int num) {
    // Check if the number is not in the current row and column
    for (int x = 0; x < N; x++) {
        if (grid[row][x] == num || grid[x][col] == num) {
            return false;
        }
    }

    // Check the 3x3 box
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }
    return true;
}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(vector<vector<int>>& grid) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            // Find an empty cell (represented by 0)
            if (grid[row][col] == 0) {
                // Try numbers 1 to 9
                for (int num = 1; num <= 9; num++) {
                    if (isSafe(grid, row, col, num)) {
                        // Place the number
                        grid[row][col] = num;

                        // Recursively try to solve the rest of the grid
                        if (solveSudoku(grid)) {
                            return true;
                        }

                        // If it doesn't lead to a solution, reset the cell
                        grid[row][col] = 0;
                    }
                }
                return false; // Trigger backtracking
            }
        }
    }
    return true; // Solved
}

int main() {
    // Example Sudoku grid (0 represents empty cells)
    vector<vector<int>> grid = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (solveSudoku(grid)) {
        printGrid(grid);
    } else {
        cout << "No solution exists" << endl;
    }

    return 0;
}