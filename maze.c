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
    int col, row;
    char val;
    maze_t* maze = (maze_t*)malloc(sizeof(maze_t));
    FILE* file = fopen(fileName, "r");
    fscanf(file, "%d %d\n", &col, &row);
    maze->cells = (char**)malloc(sizeof(row*sizeof(char*)));
    int i = 0;
    for (i = 0; i<row; i++) {
        maze->cells[i] = (char*)malloc(sizeof(col*sizeof(char)));
    }
    for (i = 0; i<row; i++) {
        for (int j = 0; j<=col; j++) {
            if (j==col) {
                fscanf(file, "%c", &val);
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
    int i = 0;
    for (i = 0; i<maze->height; i++) {
        free(maze->cells[i]);
    }
    free(maze->cells);
    free(maze);
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
    int i = 0;
    for (i = 0; i<maze->height; i++) {
        for (int j = 0; j<=maze->width; j++) {
            if (j==maze->width) {
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
    if (maze->cells[row][col]!=' ' && maze->cells[row][col]!='S') {
        return 0;
    }
    if (maze->cells[row][col]=='E') {
        return 1;
    }
    if (maze->cells[row][col]!='S') {
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
    if (maze->cells[row][col]!='S') {
        maze->cells[row][col] = '~';
    }
    return 0;
}
