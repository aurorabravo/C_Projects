// Sieve of Eratosthenes.  A quick way to find primes and a good application
// for our arbitrary-sized binary number.  We use a bit to keep up with
// whether or not each number is composite.

#include <stdio.h>
#include <stdlib.h>

#include "Binary.h"

// Test for primes up to this limit
#define LIMIT 100000000

int main()
{
  // Packed array of bits for flags, a bit for each value up to limit.
  // Flag is set if its index is composite.
  Binary *composite = makeBinary( LIMIT );

  // For each possible prime up to the square root of our range.
  for ( int i = 2; i * i < LIMIT; i++ ) {
    // Is i prime?
    if ( ! getBit( composite, i ) ) {
      // If so, mark all of its multiples as prime, skipping
      // past any multiples we would have already marked.
      for ( int j = i * i; j < LIMIT; j += i )
        setBit( composite, j, 1 );
    }
  }

  // That was the hard part, now, the values that never got marked
  // should be the primes.
  for ( int i = 2; i < LIMIT; i++ )
    if ( ! getBit( composite, i ) )
      printf( "%d\n", i );

  return EXIT_SUCCESS;
}
