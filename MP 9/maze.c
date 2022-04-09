/*
    This code contains functions used in main.c. The overall goal of this program is to solve a maze given in the form of a
    .txt file. From there it will scan the file and solve the maze. Dimensions of the maze are given in the first line while
    the rest of the text file contains the maze structure. S represents the start of the maze, E represents the end of the
    maze, space represents the path, and % represents a wall. When solving the maze, * is used to represent the solution path 
    and ~ is used to represent a backtracked path. The algorithm used for the code is based of the depth-first search searching
    algorithm. A list of functions present in the code is given below:
        1. createMaze
        2. destroyMaze
        3. printMaze
        4. solveMazeDFS
    
    Explanations for each function and their inputs, outputs, and effects are detailed with functions.

    Algorithms used for functions:
        createMaze
            Creates maze struct by reading .txt file and initializing variables from it. Used C file I/O to read and scan file. From
            there variables inside struct were initialized. 2D array was initialized by allocating memory for the double pointer for
            first index and then initializing the pointers for the double pointers for second index.
        destroyMaze
            Frees memory of maze struct. First frees the memory in arrays in the second index of the 2D array. Then it frees the memory
            inside the first index of the 2D array. Finally, it frees the struct by freeing the memory of all the other variables.
        printMaze
            Simple for loops were used to iterate through every element inside the 2D array and print it.
        solveMazeDFS
            Used given algorithm from MP website. First checks if index is in range of maze. Then checks if cell is empty or not. After that
            it checks if the maze has reached the end. If it passes all those cases, then it marks the cell as a solution path. Following that,
            the function will go up, down, left, and right of the current cell to check if it is a possible solution. If it fails all of those
            cases, the function will backtrack back and mark the cell as visited and return false at the very end.


    Matthew Wei
    mswei2
    April 9, 2022
*/

#include <stdio.h>
#include <stdlib.h>
#include "maze.h"


/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    int col, row, i, j;             //i and j had to be declared outside because of compiling issues with C version
    char val;
    maze_t* maze = (maze_t*)malloc(sizeof(maze_t));
    FILE* file = fopen(fileName, "r");
    fscanf(file, "%d %d\n", &col, &row);
    maze->cells = (char**)malloc(row*sizeof(char*));
    for (i = 0; i<row; i++) {
        maze->cells[i] = (char*)malloc(col*sizeof(char));
    }
    for (i = 0; i<row; i++) {
        for (j = 0; j<=col; j++) {
            if (j==col) {                   //Checks if end of line has been reached
                fscanf(file, "%c", &val);   //Reads new line character
                continue;
            }
            fscanf(file, "%c", &val);
            maze->cells[i][j] = val;
            if (val=='S') {
                maze->startRow = i;
                maze->startColumn = j;
            } else if (val=='E') {
                maze->endRow = i;
                maze->endColumn = j;
            }
        }
    }
    fclose(file);
    maze->width = col;
    maze->height = row;
    return maze;
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
    int i;
    for (i = 0; i<maze->height; i++) {      //Frees cells[i][j]
        free(maze->cells[i]);
    }
    free(maze->cells);                      //Frees cells[i]
    free(maze);                             //Frees other variables
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
    int i, j;
    for (i = 0; i<maze->height; i++) {
        for (j = 0; j<=maze->width; j++) {
            if (j==maze->width) {           //Checks if end of line has been reached
                printf("\n");
                continue;
            }
            printf("%c", maze->cells[i][j]);
        }
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
    if (col<0 || col>=maze->width || row<0 || row>=maze->height ) {
        return 0;
    }
    if (maze->cells[row][col]=='%' || maze->cells[row][col]=='*' || maze->cells[row][col]=='~') {
        return 0;
    }
    if (maze->cells[row][col]=='E') {
        maze->cells[maze->startRow][maze->startColumn] = 'S';     //If end is reached, mark start cell back to S
        return 1;
    }
    if (maze->cells[row][col]!='E') {
        maze->cells[row][col] = '*';
    }
    if (solveMazeDFS(maze, col-1, row)) {
        return 1;
    }
    if (solveMazeDFS(maze, col+1, row)) {
        return 1;
    }
    if (solveMazeDFS(maze, col, row-1)) {
        return 1;
    }
    if (solveMazeDFS(maze, col, row+1)) {
        return 1;
    }
    if (maze->cells[row][col]!='S' && maze->cells[row][col]!='E') {
        maze->cells[row][col] = '~';
    }
    return 0;
}