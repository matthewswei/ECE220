//Function for generating three d6 rolls
<<<<<<< HEAD

void roll_three(int* one, int* two, int* three){

=======
#include <stdlib.h>

void roll_three(int* one, int* two, int* three){
    *one = rand() % 6 + 1;
    *two = rand() % 6 + 1;
    *three = rand() % 6 + 1;
>>>>>>> 400339c868a0542169d5293fe4701c6acf96fa94
}
