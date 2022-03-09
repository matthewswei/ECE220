/*
    This code contains 3 different functions that are used in main.c. The overall program is a game of life simulator where
    a table of 1s and 0s are created with a given number of rows and columns. 1s represent a living cell and 0s represent a
    dead cell. The game overall states that if a cell has two or three alive neightbors, then it will remain alive. If a dead cell
    has three alive neighbors, then it will become alive. Any other number will result in the cell to be dead due to under or
    overpopulation. The code in this file is used to determine the number of live neighbors, update the board, and determine
    if the board is stable (doesn't change over time). The three functions are:
        1. countLiveNeighbor
        2. updateBoard
        3. aliveStable
    
    Algorithms used for functions:
        countLiveNeighbor
            Implemented the given alorigthm. Used a counter to keep track of how many alive cells are around desired cell. Used
            two loops to access neighbors of cell, one for the row and one for the column. Two if statements were also used in-
            junction with the loops to check if the cell was in a corner or boundary. The counter only increments if the neighbor
            cell being checked is within the range and does not equal the current cell being checked.
        updateBoard
            Used similar strategy with two for loops to increment through all cells. Created temporary array to hold the new values
            of the board without ruining the original board. countLiveNeighbor was used to get the number of live neighbors around
            a certain cell to determine if it lives or dies. After the temporary board is updated with the new values, it copies the
            temporary board onto the actual board.
        aliveStable
            Copied the board onto a temporary board. Then used updateBoard on the temporary board to get the board after everything is
            updated. From there, a loop is used to check every cell in the temporary board to the original board to determine if the
            boards are the same or not.

    Matthew Shuyu Wei
    mswei2
    March 9, 2022
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

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col) {
    int alive = 0;

    //loop that increments through all neighbors
    for (int i = row-1; i<=row+1;i++) {
        if (i>=0 && i<boardRowSize) {   //Checks if cell is within board
            for (int j = col-1; j<=col+1;j++) {
                if (j>=0 && j<boardColSize) {   //Checks if cell is within board
                    if (i!=row || j!=col) {     //Checks if neighbor cell being checked is origin
                        if (board[j+boardColSize*i]==1) {   //Checks if cell is alive
                            alive++;
                        }
                    }
                }
            }
        }  
    }
    return alive;
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
    int temp[boardRowSize*boardColSize];    //Creates temporary board

    //Goes through each cell in board and finds its alive neighbor count
    for (int i = 0; i<boardRowSize; i++) {
        for (int j = 0; j<boardColSize; j++) {
            int alive = countLiveNeighbor(board, boardRowSize, boardColSize, i, j); //Gets alive neightbor count

            //Updates temp board with the new values determined from the alive neightbors
            if (alive<2 || alive>3) {
                temp[j+i*boardColSize] = 0;
            } else if (alive==3) {
                temp[j+i*boardColSize] = 1;
            } else {
                temp[j+i*boardColSize] = board[j+i*boardColSize];
            }
        }
    }

    //Copies new values onto original board
    int spot = 0;
    while (spot<boardRowSize*boardColSize) {
        board[spot] = temp[spot];
        spot++;
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
int aliveStable(int* board, int boardRowSize, int boardColSize) {
    //Creates copy of board
    int temp[boardRowSize*boardColSize];
    int spot = 0;
    while (spot<boardRowSize*boardColSize) {
        temp[spot] = board[spot];
        spot++;
    }

    updateBoard(temp, boardRowSize, boardColSize);  //Gets the next step of the game

    //Checks if the cells stay the same in the next step and returns its respect value
    int i = 0;
    while(i<boardRowSize*boardColSize) {
        if (temp[i]!=board[i]) {
            return 0;
        }
        i++;
    }
    return 1;
}