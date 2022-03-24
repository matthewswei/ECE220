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
  assert(i>=0 && i<9 && j>-0 && j<9);
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

// Function: not_empty
// Returns non-empty cell
int not_empty(int* row, int* col, const int sudoku[9][9]) {
  for (int i = 0; i<9; i++) {
    for (int j = 0; j<9; j++) {
      if (sudoku[i][j]!=0) {
        *row = i;
        *col = j;
        return 1;
      }
    }
  }
  return 0;
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





