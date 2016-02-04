#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "Binary.h"

int main()
{
  // A few of binary numbers.
  Binary *a = stringToBinary( "11001010" );
  Binary *b = stringToBinary( "10010111" );
  Binary *c = makeBinary( 8 );

  // Show off some of what these binary values can do.

  // Print them out, we have to convert them to a dynamically allocated
  // string first.
  char *str;
  str = binaryToString( a );
  printf( "a = %s\n", str );
  free( str );

  str = binaryToString( b );
  printf( "b = %s\n", str );
  free( str );

  // We have functions for bitwise operations.
  orBinary( c, a, b );
  str = binaryToString( c );
  printf( "a | b = %s\n", str );
  free( str );

  // We have functions for bit shifting.
  shiftLeft( c, b, 3 );
  str = binaryToString( c );
  printf( "b << 3 = %s\n", str );
  free( str );

  // Free our three values now that we're done.
  freeBinary( a );
  freeBinary( b );
  freeBinary( c );

  return EXIT_SUCCESS;
}
