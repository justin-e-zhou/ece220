  #include "sudoku.h"
  #include <stdio.h>

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

/********************INTRO PARAGRAPH**********************
 * This program is designed to implement all functions
 * necessary to recursively solve a sudoku puzzle.
 *
 * is_val_in_row finds whether the val is present in the
 * specified row
 *
 * is_val_in_col finds whether the val is present in the
 * specified col
 *
 * is_val_in_3x3_zone finds whether the val is present in
 * its appropriate 3x3 zone
 *
 * is_val_valid uses the previous three tests to determine
 * if the given value fits into the given cell
 *
 * solve_sudoku uses all previous functions to recursively
 * solve its given sudoku puzzle. It finds the first empty
 * cell, if there is one, then fills it with a valid value.
 * It then calls the function again to recursively fill the
 * remaining cells until the board is filled or until it
 * returns false. The filled number is then incremented
 * and it is recursively filled again.
*/

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO
  int c;
  for(c = 0; c < 9; c++){   //parse through row, if value matches, return true
    if(sudoku[i][c] == val){
      return 1;
    }
  }
  return 0;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO
  int r;
  for(r = 0; r < 9; r++){   //parse through column, if value matches, return true
    if(sudoku[r][j] == val){
      return 1;
    }
  }
  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO
  int r, c;
  if(i>=0 && i<3 && j>=0 && j<3){ //if in top right 3x3, if value matches, return true
    for(r = 0; r < 3; r++){
      for(c = 0; c < 3; c++){
        if(sudoku[r][c]==val){
          return 1;
        }
      }
    }
  }
  if(i>=0 && i<3 && j>=3 && j<6){ //if in top middle 3x3, if value matches, return true
    for(r = 0; r < 3; r++){
      for(c = 3; c < 6; c++){
        if(sudoku[r][c]==val){
          return 1;
        }
      }
    }
  }
  if(i>=0 && i<3 && j>=6 && j<9){ //if in top left 3x3, if value matches, return true
    for(r = 0; r < 3; r++){
      for(c = 6; c < 9; c++){
        if(sudoku[r][c]==val){
          return 1;
        }
      }
    }
  }
  if(i>=3 && i<6 && j>=0 && j<3){ //if in middle right 3x3, if value matches, return true
    for(r = 3; r < 6; r++){
      for(c = 0; c < 3; c++){
        if(sudoku[r][c]==val){
          return 1;
        }
      }
    }
  }
  if(i>=3 && i<6 && j>=3 && j<6){ //if in middle 3x3, if value matches, return true
    for(r = 3; r < 6; r++){
      for(c = 3; c < 6; c++){
        if(sudoku[r][c]==val){
          return 1;
        }
      }
    }
  }
  if(i>=3 && i<6 && j>=6 && j<9){ //if in middle left 3x3, if value matches, return true
    for(r = 3; r < 6; r++){
      for(c = 6; c < 9; c++){
        if(sudoku[r][c]==val){
          return 1;
        }
      }
    }
  }
  if(i>=6 && i<9 && j>=0 && j<3){ //if in botton right 3x3, if value matches, return true
    for(r = 6; r < 9; r++){
      for(c = 0; c < 3; c++){
        if(sudoku[r][c]==val){
          return 1;
        }
      }
    }
  }
  if(i>=6 && i<9 && j>=3 && j<6){ //if in bottom middle 3x3, if value matches, return true
    for(r = 6; r < 9; r++){
      for(c = 3; c < 6; c++){
        if(sudoku[r][c]==val){
          return 1;
        }
      }
    }
  }
  if(i>=6 && i<9 && j>=6 && j<9){ //if in bottom left 3x3, if value matches, return true
    for(r = 6; r < 9; r++){
      for(c = 6; c < 9; c++){
        if(sudoku[r][c]==val){
          return 1;
        }
      }
    }
  }
  return 0;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO
  if(is_val_in_row(val,i,sudoku)==0 && is_val_in_col(val,j,sudoku)==0 && is_val_in_3x3_zone(val,i,j,sudoku) == 0){   //if all 3 checks return 0, the value is valid
    return 1;
  }
  return 0;
  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.
  int i, j, row, col, num;
  int flag = 1;
  for(i = 0; i < 9 && flag; i++){
    for(j = 0; j < 9 && flag; j++){ //check for first empty cell
      if(sudoku[i][j]==0){
        flag = 0;                   //set unfilled row and col to i and j, and set flag to 0
        row = i;
        col = j;
      }
    }
  }
  if(flag == 1){    //if board is filled, return 1
    return 1;
  }
  for(num = 1; num <= 9; num++){      //loop through possible values to fill cells
    if(is_val_valid(num,row,col,sudoku)==1){
      sudoku[row][col] = num;         //if num is valid, set cell
      if(solve_sudoku(sudoku)==1){    //then recurse until it returns 0 or 1
        return 1;                     //return 1 if done
      }
      sudoku[row][col] = 0;           //if does not recurse sucessfully, clear cell
    }                                 //and increment num
  }
  return 0;                           //return 0 if no values work
  // END TODO.
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





