#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "Binary.h"

/**
  @file driver.c
  @author Aurora Bravo (aibravoe@ncsu.edu)

  This program tests the functions of Binary.h using assert().
  This program exists in success if all the tests pass.

*/

// Test left shift
/*void test13()
{
  Binary *a = stringToBinary( "1111111111111111100000000000000000111111111111111110000000000000000011" );
  Binary *b = makeBinary( 70 );

  shiftLeft( b, a, 1 );

  char *str;
  str = binaryToString( b );
  assert( strcmp( str, "1111111111111111000000000000000001111111111111111100000000000000000110" ) == 0 );
  free( str );

  freeBinary( b );
  b = makeBinary( 60 ); 
  shiftLeft( b, a, 10 );

  str = binaryToString( b );
  assert( strcmp( str, "1111111000000000000000001111111111111111100000000000000000110000000000" ) == 0 );
  free( str );

  freeBinary( b );
  b = makeBinary( 100 );
  shiftLeft( b, a, 75 );

  str = binaryToString( b );
  assert( strcmp( str, "0000000000000000000000000000000000000000000000000000000000000000000000" ) == 0 );
  free( str );

  shiftLeft( a, a, 5 );

  str = binaryToString( a );
  assert( strcmp( str, "1111111111110000000000000000011111111111111111000000000000000001100000" ) == 0 );
  free( str );

  freeBinary( a );
  freeBinary( b );
}

// Test right shift
void test14()
{
  Binary *a = stringToBinary( "1111111111111111100000000000000000111111111111111110000000011111111111" );
  Binary *b = makeBinary( 70 );

  logicalShiftRight( b, a, 1 );

  char *str;
  str = binaryToString( b );
  assert( strcmp( str, "0111111111111111110000000000000000011111111111111111000000001111111111" ) == 0 );
  free( str );

  freeBinary( b );
  b = makeBinary( 60 );
  logicalShiftRight( b, a, 10 );

  str = binaryToString( b );
  assert( strcmp( str, "0000000000111111111111111110000000000000000011111111111111111000000001" ) == 0 );
  free( str );

  freeBinary( b );
  b = makeBinary( 100 );
  logicalShiftRight( b, a, 75 );

  str = binaryToString( b );
  assert( strcmp( str, "0000000000000000000000000000000000000000000000000000000000000000000000" ) == 0 );
  free( str );

  logicalShiftRight( a, a, 5 );

  str = binaryToString( a );
  assert( strcmp( str, "0000011111111111111111000000000000000001111111111111111100000000111111" ) == 0 );
  free( str );

  freeBinary( a );
  freeBinary( b );
} */

int main()
{
  // A small-ish binary number to use in our tests.
  Binary *a = stringToBinary( "111110000010101" );

  // A larger one to use in tests, something none of our built-in types could handle.
  // Remember, this syntax concatenates these two literal strings.
  Binary *b = stringToBinary( "01001011101110101000100010111000101010010111010101"
                              "10101010010000101011111001010001010010001000000001" );

  // Try out the length function.
  assert( getLength( a ) == 15 );

  // Try out getting and setting individual bits.
  assert( getBit( a, 0 ) == 1 );

  setBit( a, 1, 1 );
  assert( getBit( a, 1 ) == 1 );

  // See if a binary value converts to the right string.
  char *str;
  str = binaryToString( a );
  assert( strcmp( str, "111110000010111" ) == 0 );
  free( str );

  resizeBinary(a, 20);
  assert( getLength(a) == 20);
  resizeBinary(a, 15);
  assert( getLength(a) == 15);

  // Make an binary value for holding results.
  Binary *result = makeBinary( 100 );
  orBinary( result, a, b );
  assert( getBit( result, 0 ) == 1 );
  assert( getBit( result, 1 ) == 1 );

  andBinary( result, a, b );
  assert( getBit( result, 0 ) == 1 );
  assert( getBit( result, 1 ) == 0 );

  xorBinary( result, a, b );
  assert( getBit( result, 0 ) == 0 );
  assert( getBit( result, 1 ) == 1 );

  complementBinary(result, a);
  assert( getBit( result, 0 ) == 0 );
  assert( getBit( result, 3 ) == 1 );

  Binary *c = stringToBinary( "11111000001010100000" );
  //printf("OriginalR: %s\n", binaryToString(c));
  logicalShiftRight(a, c, 5);
  //printf("ShiftedR:  %s\n", binaryToString(a));
  assert( getBit( a, 0 ) == 1 );
  assert( getBit( a, 1 ) == 0 );
  assert( getBit( a, 2 ) == 1 );
  assert( getBit( a, 5 ) == 0 ); 
  assert( getBit( a, 6 ) == 0 );
  assert( getBit( a, 7 ) == 0 );
  
  Binary *d = stringToBinary( "11111000001010111111" );
  //printf("OriginalL: %s\n", binaryToString(d));
  shiftLeft(a, d, 5);
  //printf("ShiftedL:  %s\n", binaryToString(a));
  assert( getBit( a, 0 ) == 0 );
  assert( getBit( a, 1 ) == 0 );
  assert( getBit( a, 2 ) == 0 );
  assert( getBit( a, 5 ) == 1 );
  assert( getBit( a, 6 ) == 1 );
  assert( getBit( a, 7 ) == 1 );
  assert( getBit( a, 10) == 1 );
  assert( getBit( a, 11) == 0 );
  assert( getBit( a, 12) == 1 );


  freeBinary( a );
  freeBinary( b );
  freeBinary( c );
  freeBinary( d );
  freeBinary( result );

  //test13();
  //test14();

  return EXIT_SUCCESS;
}
