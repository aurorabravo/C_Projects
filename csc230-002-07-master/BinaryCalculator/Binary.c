#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Binary.h"

/**
    @file Binary.c
    @author Aurora Bravo (aibravoe@ncsu.edu)

    This program performs a few basic binary operations such as
    and, xor, complement, shift right, and shift left. This program
    also includes functions that get the length of a binary, resize a binary,
    and convert binary to string and vice versa. This program
    needs a test driver to run.
*/

/** Size of a byte. */
#define BYTESIZE 8

/**
    Type used for an opaque pointer to a Binary value.
*/
struct BinaryTag {
    char* BinaryString;
    int length;
    int chars;
};

/** Create a binary value containing a particular number of bits, all
    initialized to zero.  Behavior is undefined if length is netagive.
    @param length number of bits in the new value.
    @return pointer to a new Binary value.
*/
Binary *makeBinary( int length )
{
    if (length < 0) {
        return NULL;
    }
    int chars = length / BYTESIZE;
    if ( length % BYTESIZE > 0 ) {
        chars++;
    }
    char* line = (char*) calloc(chars+1, sizeof(char));
    Binary *result = calloc(1, sizeof(Binary));
    result->BinaryString = line;
    result->length = length;
    result->chars = chars;
    return result;
}

/** Create a binary value with bits given as a string one or more '1'
    and '0' characters, high-bit first.  Returns NULL if the given
    string isn't valid.
    @param src string containing the bit sequence.
    @return pointer to a new Binary value.
*/
Binary *stringToBinary( const char *src )
{
    int len = strlen(src);
    //printf("len: %d string: %s\n", len, src);
    if (len == 0) {
        return NULL;
    }

    for (int i=0; i<len; i++) {
        if (src[i] != '0' && src[i] != '1') {
            return NULL;
        }
    }
    //printf("still in stringToBinary\n");
    char *reverse = (char*) calloc(len+1, sizeof(char));
    for (int i=0; i<len; i++) {
        reverse[i] = src[len-i-1];
    }
    //printf("reverse: %s\n", reverse);

    Binary *bin = makeBinary(len);
    for (int i=0; i<len; i++) {
        setBit(bin, i, reverse[i]-'0' );
    }
    free(reverse);
    //printf("bin length: %d or %d\n", bin->length, getLength(bin));
    return bin;
}

/** Return a dynamically allocated, null terminated string containing
    the sequence of bits in src as '0' and '1' characters, high bit
    first.
    @param src binary value to be converted to a string
    @return string representing the bit sequence in src.
*/
char *binaryToString( Binary const *src )
{
    int len = src->length;
    char* result = (char*) calloc(len+1, sizeof(char));
    for (int i=0; i<len; i++) {
        result[i] = getBit(src, i)+'0';
    }

    char *reverse = (char*) calloc(len+1, sizeof(char));
    for (int i=0; i<len; i++) {
        reverse[i] = result[len-i-1];
    }

    reverse[len] = '\0';
    free(result);
    return reverse;
}

/** Free memory used to represent a binary value.
    @param val Binary value being freed.
*/
void freeBinary( Binary *val )
{
    free(val->BinaryString);
    free(val);
}

/** Return the number of bits in the given binary value.
    @param val Binary value being queried.
    @return the number of bits in val.
*/
int getLength( Binary const *val )
{
    return val->length;
}

/** Reallocate the storage for val so that it now has room for length
    bits.  If length is greater than the previous length, zero bits
    will be appended to the high-order end of val.  Remaining bits
    will be unchanged.  If the given length is shorter than the previous length,
    the Binary will be shortened, discarding high-order bits and leaving remaining
    bits unchanged.  Behavior is undefined if length is negative.
    @param val Binary value to resize.
    @param length new length for this binary value
*/
void resizeBinary( Binary *val, int length )
{
    if (length<0) {
        return;
    }
    int originalLength = val->length;
    if (length == originalLength) {
        return;
    }

    char* str = binaryToString(val);
    //printf("str (original): %s\n", str);
    if (length > originalLength) {
        int diff = length - originalLength;
        //printf("diff: %d\n", diff);
        char *zeroes = (char*) calloc(diff+1, sizeof(char));
        for (int i=0; i<diff; i++) {
            zeroes[i] = '0';
        }
        zeroes[diff] = '\0';
        //printf("zeroes: %s\n", zeroes);
        char *resultString = (char*) calloc(length+1, sizeof(char));
        strcat(resultString, zeroes);
        strcat(resultString, str);

        Binary *newVal = stringToBinary(resultString);
        val->length = newVal->length;
        val->chars = newVal->chars;
        free(val->BinaryString);
        val->BinaryString = newVal->BinaryString;

        free(resultString);
        free(zeroes);
        free(newVal); //added
        // do realloc on binary & set higher end bites to 0

    } else if (length < originalLength) {
        char *resultString = calloc(length+1, sizeof(char));
        int diff = originalLength - length;
        strncpy(resultString, str+diff, length);
        Binary *newVal = stringToBinary(resultString);
        val->length = newVal->length;
        val->chars = newVal->chars;
        free(val->BinaryString);
        val->BinaryString = newVal->BinaryString;
        free(resultString);
        free(newVal); //added
        //bites % 8 + add 1 if remidner
        //call realloc with smaller size
    }

    free(str);
}

/** Return the value of a single bit in a binary value.  Bit zero is
    considered the low-order bit, and behavior is undefined if index
    is greater than or equal to the length of the given binary value.
    @param val binary value to be examined.
    @param index index of the bit, with zero being the lowest-order bit.
    @return value of the bit, zero or one.
*/
int getBit( Binary const *val, int index )
{
    int byte = index / BYTESIZE;
    int rem = index % BYTESIZE;

    return val->BinaryString[byte] >> rem & 1;
}

/** Set the value of a single bit in a binary value.  Bit zero is
    considered the low-order bit, and behavior is undefined if index
    is greater than or equals to the length of the given binary value.
    @param val binary value to be modified.
    @param index index of the bit of val being modified.
    @param bit new value for the bit, zero clears the bit, anything else sets it.
*/
void setBit( Binary *val, int index, int bit )
{
    int byte = index / BYTESIZE;
    int rem = index % BYTESIZE;
    
    int currentValue = val->BinaryString[byte] >> rem & 1;

    int multiplyer = 1;
    for (int i=0; i<rem; i++) {
        multiplyer *= 2;
    }

    //printf("setBit. index: %d bit: %d currentValue: %d\n", index, bit, currentValue);
    if (currentValue == 0 && bit == 1) {
        val->BinaryString[byte] += multiplyer;
    } else if (currentValue == 1 && bit == 0) {
        val->BinaryString[byte] -= multiplyer;
    }
}

/** Overwrite the value of dest with the bitwise and of values a and
    b.  The dest value is resized if necessary so its length is equal
    to the longer of a and b.  If a and b are not the same length,
    zeros are used for high-order bits not present in the shorter
    operand.
    @param dest Binary value where the result is stored.
    @param a left-hand operand
    @param b right-hand operand
*/
void andBinary( Binary *dest, Binary const *a, Binary const *b )
{
    int maxLength = a->length;
    if (b->length > maxLength) {
        maxLength = b->length;
    }
    char *astring = binaryToString(a);
    char *bstring = binaryToString(b);
    Binary *aResizable = stringToBinary(astring);
    Binary *bResizable = stringToBinary(bstring);
    resizeBinary(aResizable, maxLength);
    resizeBinary(bResizable, maxLength);
    resizeBinary(dest, maxLength);

    dest->chars = aResizable->chars;
    dest->length = aResizable->length;
    for (int i=0; i<aResizable->chars; i++){
        //printf("going through chars: %d\n", i);
        dest->BinaryString[i] =
            aResizable->BinaryString[i] &
            bResizable->BinaryString[i];
    }
    free(astring);
    free(bstring);
    freeBinary(aResizable);
    freeBinary(bResizable);
}

/** Overwrite the value of dest with the bitwise or of values a and b.
    As with andBinary(), dest is resized if necessary and high-order
    zeros are assumed for the shorter operand.
    @param dest Binary value where the result is stored.
    @param a left-hand operand
    @param b right-hand operand
*/
void orBinary( Binary *dest, Binary const *a, Binary const *b )
{
    int maxLength = a->length;
    if (b->length > maxLength) {
        maxLength = b->length;
    }
    char *astring = binaryToString(a);
    char *bstring = binaryToString(b);
    Binary *aResizable = stringToBinary(astring);
    Binary *bResizable = stringToBinary(bstring);
    resizeBinary(aResizable, maxLength);
    resizeBinary(bResizable, maxLength);
    resizeBinary(dest, maxLength);

    dest->chars = aResizable->chars;
    dest->length = aResizable->length;
    for (int i=0; i<aResizable->chars; i++){
        //printf("going through chars: %d\n", i);
        dest->BinaryString[i] =
            aResizable->BinaryString[i] |
            bResizable->BinaryString[i];
    }
    //printf("Went through all chars!\n");
    //printf("dest: %s\n", binaryToString(dest));
    free(astring);
    free(bstring);
    freeBinary(aResizable);
    freeBinary(bResizable);
}

/** Overwrite the value of dest with the bitwise exclusive or of
    values a and b.  As with andBinary(), dest is resized if necessary
    and high-order zeros are assumed for the shorter operand.
    @param dest Binary value where the result is stored.
    @param a left-hand operand
    @param b right-hand operand
*/
void xorBinary( Binary *dest, Binary const *a, Binary const *b )
{
    int maxLength = a->length;
    if (b->length > maxLength) {
        maxLength = b->length;
    }
    char *astring = binaryToString(a);
    char *bstring = binaryToString(b);
    Binary *aResizable = stringToBinary(astring);
    Binary *bResizable = stringToBinary(bstring);
    resizeBinary(aResizable, maxLength);
    //printf("check 1 after the A resize. aResizable: %s\n", binaryToString(aResizable));
    resizeBinary(bResizable, maxLength);
    resizeBinary(dest, maxLength);

    dest->chars = aResizable->chars;
    dest->length = aResizable->length;
    for (int i=0; i<aResizable->chars; i++){
        //printf("going through chars: %d\n", i);
        dest->BinaryString[i] =
            aResizable->BinaryString[i] ^
            bResizable->BinaryString[i];
    }
    free(astring);
    free(bstring);
    freeBinary(aResizable);
    freeBinary(bResizable);
}

/** Overwrite the value of dest with the bitwise complement of src.
    The dest value is resized if necessary so its length is the same as src.

    @param dest Binary value where the result is stored.
    @param src source value to be complemented.
*/
void complementBinary( Binary *dest, Binary const *src )
{
    resizeBinary(dest, src->length);
    for (int i=0; i<src->chars; i++){
        dest->BinaryString[i] = ~(src->BinaryString[i]);
    }
}

/** Overwrite the value of dest with the result of shifting value src to
    the left by s bits.  Dest is resized if necessary so that its
    length is the same as src.  Low zeros are shifted into the
    low-order bits, and valeus shifting out of the high-order bit are
    discarded.
    @param dest Binary value where the result is stored.
    @param src source value to be bit shifted
    @param src number of bit positions to shift to the left
*/
void shiftLeft( Binary *dest, Binary const *src, int s )
{
    resizeBinary(dest, src->length);
    if (s > src->length) {
        s = src->length;
    }
    char* str = binaryToString(src);
    char* zeroes = (char*) calloc(s+1, sizeof(char));
    for (int i=0; i<s; i++) {
        zeroes[i] = '0';
    }
    zeroes[s] = '\0';
    char* shifted = (char*) calloc((src->length)-s+1, sizeof(char));
    strncpy(shifted, str+s, src->length-s);
    char* newString = (char*) calloc(strlen(zeroes)+strlen(shifted)+1, sizeof(char));
    newString[0] = '\0';
    strcat(newString, shifted);
    strcat(newString, zeroes);
    Binary *newVal = stringToBinary(newString);
    
    //strncpy(dest->BinaryString, newVal->BinaryString, strlen(newVal->BinaryString)+1);
    for (int i=0; i<newVal->chars; i++) {
        dest->BinaryString[i] = newVal->BinaryString[i];
    }
    dest->BinaryString[newVal->chars] = '\0';
/*
    printf("        str: %s\n", str);
    printf("     zeroes: %s\n", zeroes);
    printf("    shifted: %s\n", shifted);
    printf("  newString: %s\n", newString);
    printf("newVal->str: %s\n", binaryToString(newVal));
    printf("  dest->str: %s\n\n", binaryToString(dest));
*/
    free(str);
    free(zeroes);
    free(shifted);
    free(newString);
    freeBinary(newVal);
}

/** Overwrite the value of dest with the result of shifting value src to
    the right by s bits.  Dest is resized if necessary so that its
    length is the same as src.  Low zeros are shifted into the
    high-order bits, and valeus shifting out of the low-order bit are
    discarded.
    @param dest Binary value where the result is stored.
    @param src source value to be bit shifted
    @param src number of bit positions to shift to the right
*/
void logicalShiftRight( Binary *dest, Binary const *src, int s )
{
    resizeBinary(dest, src->length);
    if (s > src->length) {
        s = src->length;
    }
    char* str = binaryToString(src);
    char* zeroes = (char*) calloc(s+1, sizeof(char));
    for (int i=0; i<s; i++) {
        zeroes[i] = '0';
    }
    zeroes[s] = '\0';
    char* shifted = (char*) calloc(src->length-s+1, sizeof(char));
    strncpy(shifted, str, src->length-s);
    char* newString = (char*) calloc(strlen(zeroes)+strlen(shifted)+1, sizeof(char));
    strcat(newString, zeroes);
    strcat(newString, shifted);
    Binary *newVal = stringToBinary(newString);

    for (int i=0; i<newVal->chars; i++) {
        dest->BinaryString[i] = newVal->BinaryString[i];
    }
    dest->BinaryString[newVal->chars] = '\0';
/*    for (int i =0 ; i < src->length-s; i++) {
        setBit(dest, i, getBit(newVal, i));


    }
*/
    free(str);
    free(zeroes);
    free(shifted);
    free(newString);
    freeBinary(newVal);
}
