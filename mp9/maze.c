#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
/***********************************INTRO PARAGRAPH*******************************
 * The program implements the createMaze, destroyMaze, printMaze, and solveMazeDFS
 * functions. The createMaze function creates a maze struct and initializes all the
 * fields based on a given file. It fills a 2D array with the maze and initializes
 * the start and end indicies. The destroyMaze frees all the memory associated with
 * the maze struct. The printMaze prints the maze given the maze struct pointer.
 * The solveMazeDFS solves the maze using a recursive depth first search algorithm,
 * given the maze struct pointer and the row and column indicies of the start point.
 */

/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
  // Your code here. Make sure to replace following line with your own code.
  int i,j;
  char temp;
  maze_t* maze = malloc(sizeof(maze_t));    //create maze pointer and allocate memory for maze
  FILE *file = fopen(fileName,"r");         //open file
  fscanf(file,"%d %d\n",&(maze->width),&(maze->height));    //scan width and height
  (maze->cells) = malloc((maze->height)*sizeof(char *));    //cells = array of pointers
  for(i = 0; i < (maze->height); i++){                      //create array of chars for each pointer
    (maze->cells)[i] = malloc((maze->width)*sizeof(char));
  }
  for(i = 0; i < (maze->height); i++){    //fill each cell in the array with corresponding char
    for(j = 0; j < (maze->width)+1; j++){ //in the file
      fscanf(file,"%c",&temp);
      if(temp!='\n'){
        (maze->cells)[i][j] = temp;
      }
      if (temp=='S'){
        (maze->startColumn) = j;
        (maze->startRow) = i;
      }
      if (temp=='E'){
        (maze->endColumn) = j;
        (maze->endRow) = i;
      }
    }
  }
  fclose(file); //close file
  return maze;  //return maze pointer
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
  // Your code here.
  int i;
  for(i = 0; i < (maze->height); i++){  //free all spaces in the array
    free((maze->cells)[i]);
  }
  free(maze->cells);    //free the array of pointers
  free(maze);           //free the rest of maze
  return;
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
  // Your code here.
  int i,j;
  for(i = 0; i < (maze->height); i++){    //parse through and print the character in each
    for(j = 0; j < (maze->width); j++){   //cell of the array
      printf("%c",(maze->cells)[i][j]);
    }
    printf("\n");   //print newline
  }
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */
int solveMazeDFS(maze_t * maze, int col, int row)
{
  // Your code here. Make sure to replace following line with your own code.
  if((maze->cells)[row][col]=='E') return 1;  //base case if reach end
  if((maze->cells)[row][col]!=' '&&(maze->cells)[row][col]!='S') return 0;  //base case if the spot is not empty or the start
  if((maze->cells)[row][col]==' ') (maze->cells)[row][col] = '*';   //fill empty cell with *
  if(row<(maze->height)-1&&solveMazeDFS(maze,col,row+1)) return 1;  //check cell below
  if(col>0&&solveMazeDFS(maze,col-1,row)) return 1;                 //check cell to the left
  if(col<(maze->width)-1&&solveMazeDFS(maze,col+1,row)) return 1;   //check cell to the right
  if(row>0&&solveMazeDFS(maze,col,row-1)) return 1;                 //check cell above
  if((maze->cells)[row][col]=='*') (maze->cells)[row][col] = '~';   //fill * with ~
  return 0;
}
