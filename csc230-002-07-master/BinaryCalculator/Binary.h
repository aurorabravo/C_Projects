#ifndef _BINARY_H_
#define _BINARY_H_

/**
    Type used for an opaque pointer to a Binary value.
*/
typedef struct BinaryTag Binary;

/** Create a binary value containing a particular number of bits, all
    initialized to zero.  Behavior is undefined if length is netagive.
    @param length number of bits in the new value.
    @return pointer to a new Binary value.
*/
Binary *makeBinary( int length );

/** Create a binary value with bits given as a string one or more '1'
    and '0' characters, high-bit first.  Returns NULL if the given
    string isn't valid.
    @param src string containing the bit sequence.
    @return pointer to a new Binary value.
*/
Binary *stringToBinary( const char *src );

/** Return a dynamically allocated, null terminated string containing
    the sequence of bits in src as '0' and '1' characters, high bit
    first.
    @param src binary value to be converted to a string
    @return string representing the bit sequence in src.
*/
char *binaryToString( Binary const *src );

/** Free memory used to represent a binary value.
    @param val Binary value being freed.
*/
void freeBinary( Binary *val );

/** Return the number of bits in the given binary value.
    @param val Binary value being queried.
    @return the number of bits in val.
*/
int getLength( Binary const *val );

/** Reallocate the storage for val so that it now has room for length
    bits.  If length is greater than the previous length, zero bits
    will be appended to the high-order end of val.  Remaining bits
    will be unchanged.  If the given length is shorter than the previous length,
    the Binary will be shortened, discarding high-order bits and leaving remaining
    bits unchanged.  Behavior is undefined if length is negative.
    @param val Binary value to resize.
    @param length new length for this binary value
*/
void resizeBinary( Binary *val, int length );

/** Return the value of a single bit in a binary value.  Bit zero is
    considered the low-order bit, and behavior is undefined if index
    is greater than or equal to the length of the given binary value.
    @param val binary value to be examined.
    @param index index of the bit, with zero being the lowest-order bit.
    @return value of the bit, zero if or one.
*/
int getBit( Binary const *val, int index );

/** Set the value of a single bit in a binary value.  Bit zero is
    considered the low-order bit, and behavior is undefined if index
    is greater than or equals to the length of the given binary value.
    @param val binary value to be modified.
    @param index index of the bit of val being modified.
    @param bit new value for the bit, zero clears the bit, anything else sets it.
*/
void setBit( Binary *val, int index, int bit );

/** Overwrite the value of dest with the bitwise and of values a and
    b.  The dest value is resized if necessary so its length is equal
    to the longer of a and b.  If a and b are not the same length,
    zeros are used for high-order bits not present in the shorter
    operand.
    @param dest Binary value where the result is stored.
    @param a left-hand operand
    @param b right-hand operand
*/
void andBinary( Binary *dest, Binary const *a, Binary const *b );

/** Overwrite the value of dest with the bitwise or of values a and b.
    As with andBinary(), dest is resized if necessary and high-order
    zeros are assumed for the shorter operand.
    @param dest Binary value where the result is stored.
    @param a left-hand operand
    @param b right-hand operand
*/
void orBinary( Binary *dest, Binary const *a, Binary const *b );

/** Overwrite the value of dest with the bitwise exclusive or of
    values a and b.  As with andBinary(), dest is resized if necessary
    and high-order zeros are assumed for the shorter operand.
    @param dest Binary value where the result is stored.
    @param a left-hand operand
    @param b right-hand operand
*/
void xorBinary( Binary *dest, Binary const *a, Binary const *b );

/** Overwrite the value of dest with the bitwise complement of src.
    The dest value is resized if necessary so its length is the same as src.

    @param dest Binary value where the result is stored.
    @param src source value to be complemented.
*/
void complementBinary( Binary *dest, Binary const *src );

/** Overwrite the value of dest with the result of shifting value src to
    the left by s bits.  Dest is resized if necessary so that its
    length is the same as src.  Low zeros are shifted into the
    low-order bits, and valeus shifting out of the high-order bit are
    discarded.
    @param dest Binary value where the result is stored.
    @param src source value to be bit shifted
    @param src number of bit positions to shift to the left
*/
void shiftLeft( Binary *dest, Binary const *src, int s );

/** Overwrite the value of dest with the result of shifting value src to
    the right by s bits.  Dest is resized if necessary so that its
    length is the same as src.  Low zeros are shifted into the
    high-order bits, and valeus shifting out of the low-order bit are
    discarded.
    @param dest Binary value where the result is stored.
    @param src source value to be bit shifted
    @param src number of bit positions to shift to the right
*/
void logicalShiftRight( Binary *dest, Binary const *src, int s );

#endif
