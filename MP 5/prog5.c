/*
    This code contains 3 different functions that are used in main.c. The overall program is a Codebreaker game where there is
    a four digit number and the user has to guess the four digit number correctly while the program tells the user how many numbers
    in the guess are right or misplaced. The first function uses srand with a given seed input to set up the rand function for use 
    while also detecting if the given input is a valid seed or not. The second function generates a random solution based off of the 
    seed inputed earlier. The final function detects if the guess the user inputed was correct or not. It also scans the guess and 
    returns how many of the numbers were in the right position and how many were misplaced. The functoons mentioned above (in order)
    are:
        1. set_seed
        2. start_game
        3. make_guess

    Algorithms used for functions:
        set_seed
            Coded with sscanf to separate decimal value from non-decimal values. If sscanf returned 1, that means only one value was filled,
            meaning it was a valid seed. If any other number is returned, it means none or more than 1 type was detected so it will give an
            error message. srand is then used with the given decimal input.

        start_game
            Numbers are between 1-8 are used so rand() % 8 was used to return 8 values. The values returned are 0-7, so a one was added to the
            final value. These values are stored in the address locations of the parameters.

        make_guess
            Similar to set_seed, sscanf was used to make sure input was valid. The difference this time is that the range of the inputs had to
            also be checked. Then arrays were made containing the solution and guess as well as two arrays that determined if a given digit
            in the guess had been correct or checked. A counter was incremented with a for loop to determine how many guess digits mateched
            the solution digits exactly. Two for loops were used to determine the misplaced value. This was done by checking every solution 
            digit with the guess digits and incrementing a counter if they matched. Multiple other factors had to be checked as well, including
            if a guess digit was previously matched with a solution digit already.

    Matthew Shuyu Wei
    partners: mswei2, bmaedge2
    March 1, 2022
*/



/*			
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 */

#include <stdio.h>
#include <stdlib.h>
#include "prog5.h"

/*
 * You will need to keep track of the solution code using file scope
 * variables as well as the guess number.
 */

static int guess_number;
static int solution1;
static int solution2;
static int solution3;
static int solution4;


/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the 
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid. 
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int set_seed (const char seed_str[]) {
    int seed;
    char post[2];
    int ret = sscanf(seed_str, "%d%1s", &seed, post);   //Scans for user input. Stores digit in seed and returns how many parameter variables were filled
    if (ret==1) {                                       //Only integers were detected
        srand(seed);                    
        return 1;                                       //Returns 1 for success
    }
    printf("set seed: invalid seed\n");
    return 0;
}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above. 
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 * INPUTS: none
 * OUTPUTS: *one -- the first solution value (between 1 and 8)
 *          *two -- the second solution value (between 1 and 8)
 *          *three -- the third solution value (between 1 and 8)
 *          *four -- the fourth solution value (between 1 and 8)
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void start_game (int* one, int* two, int* three, int* four) {
    *one = solution1 = rand() % 8 + 1;                  //Stores value at address of parameters. % 8 returns 8 possible values inside 0-7
    *two = solution2 = rand() % 8 + 1;
    *three = solution3 = rand() % 8 + 1;
    *four = solution4 = rand() % 8 + 1;
    guess_number = 1;
}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str. 
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 integers, within the range 1-8). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: the following are only valid if the function returns 1 (A valid guess)
 *          *one -- the first guess value (between 1 and 8)
 *          *two -- the second guess value (between 1 and 8)
 *          *three -- the third guess value (between 1 and 8)
 *          *four -- the fourth color value (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
 *               numbers between 1 and 8), or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess) 
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */

int make_guess (const char guess_str[], int* one, int* two, int* three, int* four) {
//  One thing you will need to read four integers from the string guess_str, using a process
//  similar to set_seed
//  The statement, given char post[2]; and four integers w,x,y,z,
//  sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post)
//  will read four integers from guess_str into the integers and read anything else present into post
//  The return value of sscanf indicates the number of items sucessfully read from the string.
//  You should check that exactly four integers were sucessfully read.
//  You should then check if the 4 integers are between 1-8. If so, it is a valid guess
//  Otherwise, it is invalid.  
//  Feel free to use this sscanf statement, delete these comments, and modify the return statement as needed

    //Initialize variables
    int w,x,y,z;
    char post[2];
    int ret = sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post);
    if (1>w || w>8 || 1>x || x>8 || 1>y || y>8 || 1>z || z>8 || ret!=4) {       //Checks for valid input
        printf("make_guess: invalid guess\n");
        return 0;
    }

    //Initialize variables
    int perfect = 0;
    int misplaced = 0;
    int solution[] = {solution1, solution2, solution3, solution4};
    *one = w;
    *two = x;
    *three = y;
    *four = z;
    int guess[] = {*one,*two,*three,*four};
    int checked[] = {0,0,0,0};                  //Array telling if a guess digit was paired with solution digit
    int match[] = {0,0,0,0};                    //Array telling if guess digit was correct at certain position

    //for loop for getting how many digits were correctly matched
    for (int i = 0; i<4; i++) {
        if (solution[i]==guess[i]) {
            perfect++;
            checked[i] = 1;
            match[i] = 1;
        }
    }

    //for loop for getting how many digits were misplaced (i is index for solution)
    for (int i = 0; i<4; i++) {
        //Checks if digit was correctly matched
        if (match[i]==1) {
            continue;
        }
        //for loop comparing guess digit to solution digit (j is index for guess)
        for (int j = 0; j<4; j++) {
            //Checks if digits match, if the digit has been paired, and if the digits are in the same index
            if (guess[j]==solution[i] && checked[j] == 0 && i!=j) {
                checked[j] = 1;
                misplaced++;
                break;
            }
        }
    }

    printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n", guess_number, perfect, misplaced);
    guess_number++;
    return 1;
}


