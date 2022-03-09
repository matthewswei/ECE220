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
    int alive = 0;
    for (int i = row-1; i<=row+1;i++) {
        if (i<0 || i>=boardRowSize) {
            continue;
        }  
        for (int j = col-1; j<=col+1;j++) {
            if (j<0 || j>=boardColSize) {
                continue;
            }
            if (i!=row && j!=col) {
                if (board[j+boardColSize*i]==1) {
                    alive++;
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
    int temp[boardRowSize*boardColSize];
    for (int i = 0; i<boardRowSize; i++) {
        for (int j = 0; j<boardColSize; j++) {
            int alive = countLiveNeighbor(board, boardRowSize, boardColSize, i, j);
            if (alive<2 || alive>3) {
                temp[j+i*boardColSize] = 0;
            } else if (alive==3) {
                temp[j+i*boardColSize] = 1;
            } else {
                temp[j+i*boardColSize] = board[j+i*boardColSize];
            }
        }
    }
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
int aliveStable(int* board, int boardRowSize, int boardColSize){
    int temp[boardRowSize*boardColSize];
    int spot = 0;
    while (spot<boardRowSize*boardColSize) {
        temp[spot] = board[spot];
        spot++;
    }
    updateBoard(temp, boardRowSize, boardColSize);
    int i = 0;
    while(i<boardRowSize*boardColSize) {
        if (temp[i]!=board[i]) {
            return 0;
        }
    }
    return 1;
}

				
				
			

