/*
    This code is used in a program which will solve a sudoku puzzle with a given state represented in a .txt file. The code below
    is used in conjunction with the main.c file. Sudoku is a puzzle game in a 9x9 square format. The 9x9 squares are furthur divided
    into 9 3x3 groups. The rules of the game are pretty simply. No number can be repeated in one 3x3 square, no number can be repeated
    in a given row, and no number can be repeated in a given column. Therefore, the final solution of the puzzle will result in unique
    numbers for every row, column and 3x3 square. Numbers are 1-9 (look online for further explanations on game). The code has multiple
    functions:
        1. is_val_in_row
        2. is_val_in_col
        3. is_val_in_3x3_zone
        4. is_val_valid
        5. filled
        6. not_empty
        7. solve_sudoku
        8. print_sudoku
        9. parse_sudoku

    Explanations for each function and their roles are detailed with functions.
    
    Algorithms used for functions:
      is_val_in_row
        Simple for loop to iterate through every column with a constant row. If the value ever repeated, it would return true.
      is_val_in_col
        Same algorithm as is_val_in_row except iteration of for loop was done through every row instead of column.
      is_val_in_3x3_zone
        Used floor division to round the value down. Since squares are 3x3, cell was divided by 3 to determine which 3x3 group
        it was in. That value was assigned to the minimum range and adding 3 gave to maximum range of the 3x3 square. From there,
        two for loops were used to iterate through every cell in the 3x3 square to check for repeated values.
      is_val_valid
        Simple if statement checking if any of is_val_in_row, is_val_in_col_, or is_val_in_3x3_zone is found to have repeated values.
        If repeated, return false for invalid.
      filled
        Two for loops used to iterate through every cell in the puzzle with if statement checking if the cells are filled. If any cell
        holds 0, then the function returns false signaling that the sudoku puzzle is yet to be complete.
      not_empty
        Similar structure of two for loops are used to iterate through the puzzle to find a zero cell. When found, it sets the row
        and column variables in the calling function to the location of the zero cell.
      solve_sudoku
        Alorigthm used involves recursion. First the exiting condition is checked (all cells are filled). If not successful, then function
        finds a zero-filled cell. Afterwards, it will iterate through a for loop consisting of values 1-9 to check if the zero cell can be
        filled with any of the values. Then, it will call the solve_sudoku function again and recusion will happen again. In chance value
        doesn't work, it will set the cell back to 0 and through recusion the process will repeat again. Recusion will end when the called
        solve_sudoku funcion returns true (all cells are filled).
      print_sudoku and parse_sudoku were prewritten, so no alterations were done.

    Matthew Shuyu Wei
    mswei2
    March 24, 2022
*/

#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {
  assert(i>=0 && i<9);
  for (int j = 0; j<9; j++) {
    if (sudoku[i][j]==val) {
      return 1;
    }
  }
  return 0;
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {
  assert(j>=0 && j<9);
  for (int i = 0; i<9; i++) {
    if (sudoku[i][j]==val) {
      return 1;
    }
  }
  return 0;
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
  assert(i>=0 && i<9 && j>=0 && j<9);
  int minx = (i/3)*3;
  int maxx = minx + 3;
  int miny = (j/3)*3;
  int maxy = miny + 3;
  for (int row = minx; row<maxx; row++) {
    for (int col = miny; col<maxy; col++) {
      if (sudoku[row][col]==val) {
        return 1;
      }
    }
  }
  return 0;
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {
  assert(i>=0 && i<9 && j>=0 && j<9);
  if (is_val_in_row(val, i, sudoku) || is_val_in_col(val, j, sudoku) || is_val_in_3x3_zone(val, i, j, sudoku)) {
    return 0;
  }
  return 1;
}

// Function: filled
// Returns true if all cells in puzzle are non-zero
int filled(int sudoku[9][9]) {
  for (int i = 0; i<9; i++) {
    for (int j = 0; j<9; j++) {
      if (sudoku[i][j]==0) {
        return 0;
      }
    }
  }
  return 1;
}

// Procedure: Sets i and j in solve_sudoku to a cell with zero as its value
void not_empty(int* row, int* col, const int sudoku[9][9]) {
    for (int i = 0; i<9; i++) {
        for (int j = 0; j<9; j++) {
            if (sudoku[i][j]==0) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {
  int i, j;
  if (filled(sudoku)) {
    return 1;
  } else {
    not_empty(&i, &j, sudoku);
  }
  for (int num = 1; num <= 9; num++) { 
    if (is_val_valid(num, i, j, sudoku)) { 
      sudoku[i][j] = num; 
      if (solve_sudoku(sudoku)) {
        return 1;
      }
      sudoku[i][j] = 0; 
    }
  }
  return 0;
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}