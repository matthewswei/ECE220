/*
    This code has two different functions that are used in main.c. First is a function that checks if a value is
    prime or not and the second function prints out all the semiprimes in between two numbers. A semiprime is a number 
    that is the product of two prime numbers. This means its only factors are one, itself, and two other prime numbers. 
    This code has been prewritten, but there are errors in the code that required fixing. These errors are detailed
    below in the errors section.

    Errors:
        is_prime
            1. Return value should be equal to 1 if the number isn't checked by the for loop (2 or number)

            2. Return value for the number % i = 0 should be 0 because that means the number is not prime

        print_semiprimes
            1. The line where it sets k to the other factor of i that isn't j initally had k = i % j, which is the wrong 
            operation. Should be k = i / j because that will return the other factor, not its remainder.

            2. The if statement that checks if k is prime returns back to the loop inner loop and can potentially
            print out the same value again if the other prime factor is within the range (ie. for 6 it will print out
            6 for j = 2 and 6 again for j = 3). Function only needs semiprime printed once, so this statement needs
            to break out of the loop once executed. This is fixed by adding break.

  Matthew Shuyu Wei
  mswei2
  Febuary 22, 2022
*/

#include <stdlib.h>
#include <stdio.h>

/*
 * is_prime: determines whether the provided number is prime or not
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
    int i;
    if (number == 1) {return 0;}
    for (i = 2; i < number; i++) { //for each number smaller than it
        if (number % i == 0) { //check if the remainder is 0
            return 0;
        } else if (number == i+1) {
            return 1;
        }
    }
    return 1;
}


/*
 * print_semiprimes: prints all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
    int i, j, k;
    int ret = 0;
    for (i = a; i <= b; i++) { //for each item in interval
        //check if semiprime
        for (j = 2; j <= i; j++) {
            if (i%j == 0) {
                if (is_prime(j)) {
                    k = i/j;
                    if (is_prime(k)) {
                        printf("%d ", i);
                        break;
                    }
                }
            }
        }

    }
    printf("\n");
    return ret;

}
