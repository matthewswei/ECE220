#include "prime.h"

int is_prime(int n){
  // Return 1 if n is a prime, and 0 if it is not
<<<<<<< HEAD
=======
  if (n==1) {
    return 0;
  }
  if (n<=3) {
    return 1;
  }
  for (int i = 2; i<=n; i++) {
    if (n%i==0&&n!=i) {
      return 0;
    } else if (n==i) {
      return 1;
    }
  }
>>>>>>> 400339c868a0542169d5293fe4701c6acf96fa94
  return 0;
}

