// Uses preprocessor macros to enable/disable code for individual tests, so we can
// still link even if students don't define all the functions.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "Binary.h"

#ifdef TEST_0

// Test creation and getLength
void test0()
{
  Binary *a = stringToBinary( "111110000010101" );
  Binary *b = makeBinary( 5 );
  
  assert( getLength( b ) == 5 );
  assert( getLength( a ) == 15 );

  freeBinary( a );
  freeBinary( b );
}

#endif

#ifdef TEST_1

// Test bad creation.
void test1()
{
  Binary *a;
  a = stringToBinary( "12ab" );
  assert( a == NULL );

  a = stringToBinary( "" );
  assert( a == NULL );
}

#endif

#ifdef TEST_2

// Test getbit/setbit
void test2()
{
  Binary *a = stringToBinary( "11111111111111110000000000000000" );
  
  assert( getBit( a, 0 ) == 0 );
  setBit( a, 0, 1 );
  assert( getBit( a, 0 ) == 1 );

  assert( getBit( a, 15 ) == 0 );
  setBit( a, 15, 1 );
  assert( getBit( a, 15 ) == 1 );

  assert( getBit( a, 2 ) == 0 );
  setBit( a, 2, 1 );
  assert( getBit( a, 2 ) == 1 );

  assert( getBit( a, 3 ) == 0 );
  setBit( a, 3, 1 );
  assert( getBit( a, 3 ) == 1 );

  assert( getBit( a, 4 ) == 0 );
  setBit( a, 4, 1 );
  assert( getBit( a, 4 ) == 1 );

  assert( getBit( a, 5 ) == 0 );
  setBit( a, 5, 1 );
  assert( getBit( a, 5 ) == 1 );

  assert( getBit( a, 6 ) == 0 );
  setBit( a, 6, 1 );
  assert( getBit( a, 6 ) == 1 );

  assert( getBit( a, 7 ) == 0 );
  setBit( a, 7, 1 );
  assert( getBit( a, 7 ) == 1 );

  assert( getBit( a, 8 ) == 0 );
  setBit( a, 8, 1 );
  assert( getBit( a, 8 ) == 1 );

  assert( getBit( a, 31 ) == 1 );
  setBit( a, 31, 0 );
  assert( getBit( a, 31 ) == 0 );

  freeBinary( a );
}

#endif

#ifdef TEST_3

// Test resizing.
void test3()
{
  Binary *a = stringToBinary( "111110000010101" );
  Binary *b = makeBinary( 5 );

  resizeBinary( a, 16 );
  assert( getLength( a ) == 16 );
  
  resizeBinary( b, 10 );
  assert( getLength( b ) == 10 );

  assert( getBit( a, 15 ) == 0 );
  assert( getBit( b, 9 ) == 0 );

  freeBinary( a );
  freeBinary( b );
}

#endif

#ifdef TEST_4

// Test making shorter then longer under resize.
void test4()
{
  Binary *a = stringToBinary( "1111111111111111" );
  resizeBinary( a, 15 );
  assert( getLength( a ) == 15 );
  
  resizeBinary( a, 16 );
  assert( getLength( a ) == 16 );
  assert( getBit( a, 15 ) == 0 );
  freeBinary( a );
}

#endif

#ifdef TEST_5

// Test converting to a string to see if all bits are equal
void test5()
{
  Binary *a = stringToBinary( "111110000010101" );

  char *str;
  str = binaryToString( a );
  assert( strcmp( str, "111110000010101" ) == 0 );
  free( str );
  
  freeBinary( a );
}

#endif

#ifdef TEST_6

// Test resizing and converting to a string to see if all bits are equal
void test6()
{
  Binary *a = stringToBinary( "111110000010101" );

  resizeBinary( a, 14 );
  assert( getLength( a ) == 14 );

  char *str;
  str = binaryToString( a );
  assert( strcmp( str, "11110000010101" ) == 0 );
  free( str );
  
  resizeBinary( a, 15 );
  assert( getLength( a ) == 15 );
  assert( getBit( a, 14 ) == 0 );
  str = binaryToString( a );
  assert( strcmp( str, "011110000010101" ) == 0 );
  free( str );

  freeBinary( a );
}

#endif

#ifdef TEST_7

// Test the binary operators, with arguments of all equal length.
void test7( void (*f)( Binary *, Binary const *, Binary const * ), char *target )
{
  Binary *a = stringToBinary( "11111111111111111000000000000000001111111111111111100000000000000000" );
  Binary *b = stringToBinary( "11111111111111111111111111111111110000000000000000000000000000000000" );
  Binary *c = stringToBinary( "10101010101010101010101010101010101010101010101010101010101010101010" );
  
  f( c, a, b );

  char *str;
  str = binaryToString( c );
  assert( strcmp( str, target ) == 0 );
  free( str );

  freeBinary( a );
  freeBinary( b );
  freeBinary( c );
}

#endif

#ifdef TEST_8

// Test the binary operators, with arguments of unequal length and a destination that has to shrink
void test8( void (*f)( Binary *, Binary const *, Binary const * ), char *target )
{
  Binary *a = stringToBinary( "1111111111111111111000000000000000001111111111111111100000000000000000" );
  Binary *b = stringToBinary( "111111111111111111111111111111110000000000000000000000000000000000" );
  Binary *c = stringToBinary( "1010101010101010101010101010101010101010101010101010101010101010101010101010" );
  
  f( c, a, b );

  char *str;
  str = binaryToString( c );
  assert( strcmp( str, target ) == 0 );
  free( str );

  freeBinary( a );
  freeBinary( b );
  freeBinary( c );
}

#endif

#ifdef TEST_9

// Test the binary operators, with arguments of unequal length and a destination that has to grow
void test9( void (*f)( Binary *, Binary const *, Binary const * ), char *target )
{
  Binary *a = stringToBinary( "111111111111111111111111111111110000000000000000000000000000000000" );
  Binary *b = stringToBinary( "1111111111111111111000000000000000001111111111111111100000000000000000" );
  Binary *c = makeBinary( 6 );
  
  f( c, a, b );

  char *str;
  str = binaryToString( c );
  assert( strcmp( str, target ) == 0 );
  free( str );

  freeBinary( a );
  freeBinary( b );
  freeBinary( c );
}

#endif

#ifdef TEST_10

// Test the binary operators, with the first argument as the destination.
void test10( void (*f)( Binary *, Binary const *, Binary const * ), char *target )
{
  Binary *a = stringToBinary( "11111111111111111000000000000000001111111111111111100000000000000000" );
  Binary *b = stringToBinary( "11111111111111111111111111111111110000000000000000000000000000000000" );
  
  f( a, a, b );

  char *str;
  str = binaryToString( a );
  assert( strcmp( str, target ) == 0 );
  free( str );

  freeBinary( a );
  freeBinary( b );
}

#endif

#ifdef TEST_11

// Test the binary operators, with the second argument as the destination.
void test11( void (*f)( Binary *, Binary const *, Binary const * ), char *target )
{
  Binary *a = stringToBinary( "11111111111111111000000000000000001111111111111111100000000000000000" );
  Binary *b = stringToBinary( "11111111111111111111111111111111110000000000000000000000000000000000" );
  
  f( b, a, b );

  char *str;
  str = binaryToString( b );
  assert( strcmp( str, target ) == 0 );
  free( str );

  freeBinary( a );
  freeBinary( b );
}

#endif

#ifdef TEST_12

// Test complement
void test12()
{
  Binary *a = stringToBinary( "1111111111111111100000000000000000111111111111111110000000000000000011" );
  Binary *b = makeBinary( 70 );

  complementBinary( b, a );

  char *str;
  str = binaryToString( b );
  assert( strcmp( str, "0000000000000000011111111111111111000000000000000001111111111111111100" ) == 0 );
  free( str );

  freeBinary( b );
  b = makeBinary( 60 );
  complementBinary( b, a );

  str = binaryToString( b );
  assert( strcmp( str, "0000000000000000011111111111111111000000000000000001111111111111111100" ) == 0 );
  free( str );

  freeBinary( b );
  b = makeBinary( 100 );
  complementBinary( b, a );

  str = binaryToString( b );
  assert( strcmp( str, "0000000000000000011111111111111111000000000000000001111111111111111100" ) == 0 );
  free( str );

  complementBinary( a, a );

  str = binaryToString( a );
  assert( strcmp( str, "0000000000000000011111111111111111000000000000000001111111111111111100" ) == 0 );
  free( str );

  freeBinary( a );
  freeBinary( b );
}

#endif

#ifdef TEST_13

// Test left shift
void test13()
{
  Binary *a = stringToBinary( "1111111111111111100000000000000000111111111111111110000000000000000011" );
  Binary *b = makeBinary( 70 );
  //printf("Lengths of a and b: %d and %d\n", getLength(a), getLength(b));

  shiftLeft( b, a, 1 );

  char *str;
  str = binaryToString( b );
  //printf("OriginalStr: %s\n", binaryToString(a));
  //printf("shiftedLeft: %s\n", str);
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

#endif

#ifdef TEST_14

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
}

#endif

int main()
{

#ifdef TEST_0
  test0();
#endif
#ifdef TEST_1
  test1();
#endif
#ifdef TEST_2
  test2();
#endif
#ifdef TEST_3
  test3();
#endif
#ifdef TEST_4
  test4();
#endif
#ifdef TEST_5
  test5();
#endif
#ifdef TEST_6
  test6();
#endif
#ifdef TEST_7
  test7( andBinary, "11111111111111111000000000000000000000000000000000000000000000000000" );
  test7( orBinary, "11111111111111111111111111111111111111111111111111100000000000000000" );
  test7( xorBinary, "00000000000000000111111111111111111111111111111111100000000000000000" );
#endif
#ifdef TEST_8
  test8( andBinary, "0000111111111111111000000000000000000000000000000000000000000000000000" );
  test8( orBinary, "1111111111111111111111111111111111111111111111111111100000000000000000" );
  test8( xorBinary, "1111000000000000000111111111111111111111111111111111100000000000000000" );
#endif
#ifdef TEST_9
  test9( andBinary, "0000111111111111111000000000000000000000000000000000000000000000000000" );
  test9( orBinary, "1111111111111111111111111111111111111111111111111111100000000000000000" );
  test9( xorBinary, "1111000000000000000111111111111111111111111111111111100000000000000000" );
#endif
#ifdef TEST_10
  test10( andBinary, "11111111111111111000000000000000000000000000000000000000000000000000" );
  test10( orBinary, "11111111111111111111111111111111111111111111111111100000000000000000" );
  test10( xorBinary, "00000000000000000111111111111111111111111111111111100000000000000000" );
#endif
#ifdef TEST_11
  test11( andBinary, "11111111111111111000000000000000000000000000000000000000000000000000" );
  test11( orBinary, "11111111111111111111111111111111111111111111111111100000000000000000" );
  test11( xorBinary, "00000000000000000111111111111111111111111111111111100000000000000000" );
#endif
#ifdef TEST_12
  test12();
#endif
#ifdef TEST_13
  test13();
#endif
#ifdef TEST_14
  test14();
#endif

  return 0;
}
