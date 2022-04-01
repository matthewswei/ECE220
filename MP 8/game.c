/*
    This code contains functions for main.c. The overall functino of the program is to create the popular 2048 game in which there is some MxN board
    where an individual tile is created randomly (usually of value 2 or 4). The player has 4 moves (up,down,left,right) to make. Each move will
    shift the board towards that direction. If two tiles are the same value and they meet, then the tiles merge and their values combine. Only
    two tiles can merge together at once, so three or more tiles can't combine. Since the tiles start with 2, each combination is an exponential 
    power of 2 (2,4,8,16,32,64,128,256,512,1024,2048). The goal is to combine the tiles until the final value of 2048 is reached. The list of functions
    is listed below:
        1. make_game
        2. remake_game
        3. get_cell
        4. move_w
        5. move_s
        6. move_a
        7. move_d
        8. legal_move_check
        9. destroy_game
        10. rand_new_tile
        11. print_game
        12. process_turn

    Explanations for each function and their roles are detailed in functions.
    
    Algorithms used for functions:
        make_game
            Initialized variables in game struct. For loop was used to assign every value inside the board to -1 initially.
        remake_game
            Same exact process as in make_game, just changing names of variables.
        get_cell
            Simply if statement to check that cols and rows are within the bounds of the board. If they are, then it returns the pointer to
            said row and column location using an equation to convert 2d points to a 1d array.
        move_w
            Alorgithm starts off with two for loops, one to represent rows and one to represent columns. It goes through the array going down each
            column one by one to find a non-empty cell. If a non-empty cell is found, then another loop will iterate through that specific column
            to find the closest empty cell to the top of the column. Once found, if will shift that cell there and replace the cell's original spot
            with an empty cell. Then, it will check the cell that just moved with the cell directly above it. If they are equal, then they will combine
            and the score will update. Throughout this process, there is a value called moved to keep track if any moving was done. If moving was detected,
            it will return 1. Elsewise it will return 0. Also since no more than two cells can combine together at a time, another variable was added also
            to keep check of the last merged column to avoid combining multiple cells.
        move_s
            Exact same algorithm as move_w except it was changed so that the loops iterate from each column beginning from the bottom of the column instead
            of the top. Variables were also changed accordingly to accommodate this change.
        move_a
            Exact same algorithm as move_w except it was changed so that the loops iterate through each row instead of column starting from the left and
            moving to the right. Variables were also changed accordingly to accommodate this change.
        move_d
            Exact same algorithm as move_a except it was changed so that the loops iterate from each row beginning from the left of the row instead of the
            right. Variables were also changed accordingly to accommodate this change.
        legal_move_check
            Simple for loop to check if every spot on the board is filled yet. Then if statements are used to check the neighbors of the cell to
            ensure no moves can be combined.
    
      destroy_game, rand_new_tile, print_game, and process_turn are all given so no alterations were done.
    
    Matthew Shuyu Wei
    mswei2
    March 31, 2022
*/

#include "game.h"


game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));
    mygame->rows = rows;
    mygame->cols = cols;
    mygame->score = 0;
    for (int i = 0; i<rows*cols; i++) {
        mygame->cells[i] = -1;
    }
    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any 
	memory previously allocated is not lost in this function.	
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));
    (*_cur_game_ptr)->rows = new_rows;
    (*_cur_game_ptr)->cols = new_cols;
    (*_cur_game_ptr)->score = 0;
    for (int i = 0; i<new_rows*new_cols; i++) {
        (*_cur_game_ptr)->cells[i] = -1;
    }
	return;	
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{
    if (row>=0 && row<row*col && col>=0 && col<row*col) {
        return cur_game->cells + row*cur_game->cols + col;
    }
    return NULL;
}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can 
   not merge twice in one turn. If sliding the tiles up does not cause any 
   cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
*/
{
    int M = cur_game->rows;
    int N = cur_game->cols;
    int moved = 0;      //Tracks if board was shifted

    //Iterated through board
    for (int i = 0; i<N; i++) {
        int comb_indicator = -1;    //Tracks last combined cell to avoid combining multiple ones
        for (int j = 0; j<M; j++) {
            int cur_index = j*N + i;
            if (cur_game->cells[cur_index]!=-1) {
                int comb_index = j;             //Used as the variable for the new location of the current cell (look at line 149)
                for (int k = 0; k<j; k++) {     //Loops through current column starting from top to find empty cell
                    int index = k*N + i;
                    if (cur_game->cells[index]==-1) {   //Shifts cell to empty cell if empty cell was detected
                        cur_game->cells[index] = cur_game->cells[cur_index];
                        cur_game->cells[cur_index] = -1;
                        comb_index = k;
                        moved++;
                        break;
                    }
                }
                if (comb_index-1 != comb_indicator) {   //Combines cells if top cell is equal to current cell
                    int prev_index = (comb_index-1)*N + i;  //Gets top cell
                    int next_index = comb_index*N + i;      //Gets the location of the cell that has been shifted
                    if (cur_game->cells[prev_index]==cur_game->cells[next_index]) {   //Updates board and score if equal
                        cur_game->cells[prev_index]*=2;
                        cur_game->cells[next_index] = -1;
                        comb_indicator = comb_index - 1;
                        cur_game->score += cur_game->cells[prev_index];
                        moved++;
                    }
                }
            }  
        }
    }
    if (moved==0) {
        return 0;
    }
    return 1;
};

int move_s(game * cur_game) //slide down
{
    int M = cur_game->rows;
    int N = cur_game->cols;
    int moved = 0;
    for (int i = 0; i<N; i++) {
        int comb_indicator = M;
        for (int j = M-1; j>=0; j--) {
            int cur_index = j*N + i;
            if (cur_game->cells[cur_index]!=-1) {
                int comb_index = j;
                for (int k = M-1; k>j; k--) {
                    int index = k*N + i;
                    if (cur_game->cells[index]==-1) {
                        cur_game->cells[index] = cur_game->cells[cur_index];
                        cur_game->cells[cur_index] = -1;
                        comb_index = k;
                        moved++;
                        break;
                    }
                }
                if (comb_index+1 != comb_indicator) {
                    int prev_index = (comb_index+1)*N + i;
                    int next_index = comb_index*N + i;
                    if (cur_game->cells[prev_index]==cur_game->cells[next_index]) {
                        cur_game->cells[prev_index]*=2;
                        cur_game->cells[next_index] = -1;
                        comb_indicator = comb_index + 1;
                        cur_game->score += cur_game->cells[prev_index];
                        moved++;
                    }
                }
            }  
        }
    }
    if (moved==0) {
        return 0;
    }
    return 1;
};

int move_a(game * cur_game) //slide left
{
    int M = cur_game->cols;
    int N = cur_game->rows;
    int moved = 0;
    for (int i = 0; i<N; i++) {
        int comb_indicator = -1;
        for (int j = 0; j<M; j++) {
            int cur_index = i*M + j;
            if (cur_game->cells[cur_index]!=-1) {
                int comb_index = j;
                for (int k = 0; k<j; k++) {
                    int index = i*M + k;
                    if (cur_game->cells[index]==-1) {
                        cur_game->cells[index] = cur_game->cells[cur_index];
                        cur_game->cells[cur_index] = -1;
                        comb_index = k;
                        moved++;
                        break;
                    }
                }
                if (comb_index-1 != comb_indicator) {
                    int prev_index = i*M + comb_index-1;
                    int next_index = i*M + comb_index;
                    if (cur_game->cells[prev_index]==cur_game->cells[next_index]) {
                        cur_game->cells[prev_index]*=2;
                        cur_game->cells[next_index] = -1;
                        comb_indicator = comb_index - 1;
                        cur_game->score += cur_game->cells[prev_index];
                        moved++;
                    }
                }
            }  
        }
    }
    if (moved==0) {
        return 0;
    }
    return 1;
};

int move_d(game * cur_game){ //slide to the right
    int M = cur_game->cols;
    int N = cur_game->rows;
    int moved = 0;
    for (int i = 0; i<N; i++) {
        int comb_indicator = -1;
        for (int j = M-1; j>=0; j--) {
            int cur_index = i*M + j;
            if (cur_game->cells[cur_index]!=-1) {
                int comb_index = j;
                for (int k = M-1; k>j; k--) {
                    int index = i*M + k;
                    if (cur_game->cells[index]==-1) {
                        cur_game->cells[index] = cur_game->cells[cur_index];
                        cur_game->cells[cur_index] = -1;
                        comb_index = k;
                        moved++;
                        break;
                    }
                }
                if (comb_index+1 != comb_indicator) {
                    int prev_index = i*M + comb_index+1;
                    int next_index = i*M + comb_index;
                    if (cur_game->cells[prev_index]==cur_game->cells[next_index]) {
                        cur_game->cells[prev_index]*=2;
                        cur_game->cells[next_index] = -1;
                        comb_indicator = comb_index + 1;
                        cur_game->score += cur_game->cells[prev_index];
                        moved++;
                    }
                }
            }  
        }
    }
    if (moved==0) {
        return 0;
    }
    return 1;
};

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    int col = cur_game->cols;
    int row = cur_game->rows; 

    //Iterates through board
    for (int i = 0; i<row; i++) {
        for (int j = 0; j<col; j++) {
            int index = i*col + j;

            //Checks if cell is empty
            if (cur_game->cells[index]==-1) {
                return 1;
            }

            //Checks neighbors of cell
            int up = (i-1)*col + j;
            int down = (i+1)*col + j;
            int left = i*col + j - 1;
            int right = i*col + j + 1;
            if (cur_game->cells[index]==cur_game->cells[up] || cur_game->cells[index]==cur_game->cells[down] || cur_game->cells[index]==cur_game->cells[left] || cur_game->cells[index]==cur_game->cells[right]) {
                return 1;
            }
        }
    }
    return 0; 
}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}