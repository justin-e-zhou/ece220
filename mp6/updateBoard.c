/*******************INTRO PARAGRAPH*****************
 * This program is designed to include all the board
 * update functions for the gameoflife. It includes
 * CountLiveNeighbor which counts all the alive
 * neighbors to a givel cell; updateBoard, which
 * updates the game board to the next state given
 * an original board and its size; and aliveStable
 * which returns a 1 if the next board is identical
 * to the current board, and a 0 if the next board
 * is different from the current board
 */

/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */
int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
  int cellIndex = row*boardColSize + col;
  int neighborCount = 0;
//  int cell;
  for(int i = -1; i <= 1; i++){  //row modifier
    for(int j = -1; j <= 1; j++){  //col modifier
      //cell = *(board + cellIndex + i*boardColSize + j); //get cell value
      //if location is not at edge or corner, and cell = 1, increment neighborCount
      if(row>0 && row<(boardRowSize-1) && col>0 && col<(boardColSize-1)){
        if(*(board + cellIndex + i*boardColSize + j)==1)
          neighborCount++;
        //break;
      }
      //if location is at top edge and not at a corner, and i >= 0 and cell = 1, increment neighborCount
      if(row==0 && col>0 && col<(boardColSize-1) && i>=0){
        if(*(board + cellIndex + i*boardColSize + j)==1)
          neighborCount++;
        //break;
      }
      //if location is at left edge and not at a corner, and j >= 0 and cell = 1, increment neighborCount
      if(col==0 && row>0 && row<(boardRowSize-1) && j>=0){
        if(*(board + cellIndex + i*boardColSize + j)==1)
          neighborCount++;
        //break;
      }
      //if location is at bottom edge and not at a corner, and i <= 0 and cell = 1, increment neighborCount
      if(row==(boardRowSize-1) && col>0 && col<(boardColSize-1) && i<=0){
        if(*(board + cellIndex + i*boardColSize + j)==1)
          neighborCount++;
        //break;
      }
      //if location is at right edge and not at a corner, and j <= 0 and cell = 1, increment neighborCount
      if(col==(boardColSize-1) && row>0 && row<(boardRowSize-1) && j<=0){
        if(*(board + cellIndex + i*boardColSize + j)==1)
          neighborCount++;
        //break;
      }
      //if location is at top left corner, i >= 0 and j >=0 and cell = 1, increment neighborCount
      if(row==0 && col==0 && i>=0 && j>=0){
        if(*(board + cellIndex + i*boardColSize + j)==1)
          neighborCount++;
        //break;
      }
      //if location is at top right corner, i >= 0 and j <= 0 and cell = 1, increment neighborCount
      if(row==0 && col==(boardColSize-1) && i>=0 && j<=0){
        if(*(board + cellIndex + i*boardColSize + j)==1)
          neighborCount++;
        //break;
      }
      //if location is at bottom left corner, i <= 0 and j >= 0 and cell = 1, increment neighborCount
      if(row==(boardRowSize-1) && col==0 && i<=0 && j>=0){
        if(*(board + cellIndex + i*boardColSize + j)==1)
          neighborCount++;
        //break;
      }
      //if location is at bottom right corner, i <= 0 and j <= 0 and cell = 1, increment neighborCount
      if(row==(boardRowSize-1) && col==(boardColSize-1) && i<=0 && j<=0){
        if(*(board + cellIndex + i*boardColSize + j)==1)
          neighborCount++;
        //break;
      }
    }
  }
  //if cellLocation = 1, decrement count to avoid overcounting
  if(*(board+cellIndex) == 1)
    neighborCount--;
  return neighborCount;
}


/*
 * Update the game board to the next step.
 * Input:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
  int boardSize = boardRowSize * boardColSize;  //boardsize int
  int updatedBoard[boardSize];  //temp storage array
  int cell, liveNeighbors, location;
  //fill updatedBoard with board
  for(int i = 0; i < boardSize; i++){
    updatedBoard[i] = *(board+i);
  }
  //fill updatedBoard with updated values
  for(int i = 0; i < boardRowSize; i++){  //row modifier
    for(int j = 0; j < boardColSize; j++){  //col modifier
      location = i*boardColSize + j;  //get current location of cell
      cell=*(board+location); //Get cell value of current board cell
      liveNeighbors = countLiveNeighbor(board,boardRowSize,boardColSize,i,j); //Get number of live neighbors at current cell
      //Any live cell with fewer than two live neighbours dies, as if caused by under-population.
      if(liveNeighbors<2 && cell==1){
        updatedBoard[location] = 0;
      }
      //Any live cell with two or three live neighbours lives on to the next generation.
      if((liveNeighbors==2 || liveNeighbors==3) && cell==1){
        updatedBoard[location] = 1;
      }
      //Any live cell with more than three live neighbours dies, as if by over-population.
      if(liveNeighbors>3 && cell==1){
        updatedBoard[location] = 0;
      }
      //Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
      if(liveNeighbors==3 && cell==0){
        updatedBoard[location] = 1;
      }
    }
  }
  //replace board with updatedBoard
  for(int i = 0; i < boardSize; i++){
    *(board+i) = updatedBoard[i];
  }
}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */
int aliveStable(int* board, int boardRowSize, int boardColSize){
  int boardSize = boardRowSize*boardColSize;  //boardsize int for easier traversal
  int after[boardSize];
  for(int i = 0; i < boardSize; i++){ //fill after with current board
    after[i] = *(board+i);
  }
  updateBoard(after, boardRowSize, boardColSize); //update after so it is at the next board state
  for(int i = 0; i < boardSize; i++){
    if(*(board+i)!=after[i])  //check if the boards are equal
      return 0; //return 0 if not
  }
  return 1; //return 1 if it is
}