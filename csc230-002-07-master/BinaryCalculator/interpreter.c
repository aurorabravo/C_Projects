#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "Binary.h"
#include "Expr.h"

/**
    @file interpreter.c
    @author Aurora Bravo (aibravoe)

    This program interprets binary arithmetic given as a text file or
    through the console and outputs the result of the arithmetic
    expression to the console or the text file.
*/

/** Length for a new binary value, until it gets assigned a value */
#define DEFAULT_BINARY_LEN 32

Expr *parseXorExpr( FILE * );
Expr *parseAndExpr( FILE * );
Expr *parseShiftExpr( FILE * );
Expr *parseComplementExpr( FILE * );
Expr *parseAtomicExpr( FILE * );

/** Number of lines */
int linenum = 1;

/**
    Skip spaces and return a copy of the next non-whitespace character
    (or EOF), while leaving it on the input.
    @param input stream to read from.
    @return copy of the next non-whitespace character
*/
static int peek( FILE *input )
{
    // Skip whitespace
    int ch = fgetc( input );
    while ( isspace( ch  ) ) {
        if (ch == '\n') {
            linenum++;
        }
        ch = fgetc( input );
    }

    // Put the first non-whitespace character back on the stream.
    if ( ch != EOF )
        ungetc( ch, input );
    return ch;
}

/**
    Skip whitespace, then start consuming input, making sure it
    matches the sequence of characters given in the pat string.  If
    input doesn't match, it indicates an invalid expression.
    @param input stream to read from.
    @param pat string the input must match
*/
void match( FILE *input, char const *pat )
{
    // force skipping of spaces.
    peek( input );

    // Match input characters against the given string.
    for ( int i = 0; pat[ i ]; i++ ) {
        int ch = fgetc( input );
        if ( pat[ i ] != ch ) {
            if (ch == EOF) {
                printf("Unexpected end-of-file on line %d\n", linenum);
            } else if ( isspace(ch)) {
                printf("Unexpected whitespace on line %d\n", linenum);
            } else {
                printf( "Unexpected character '%c' on line %d\n", ch, linenum );
            }
            exit( EXIT_FAILURE );
        }
    }
}

/**
    Return true if the given character is a zero or one.
    @param ch a character to check.
    @return true if ch is 0 or 1
*/
bool isBinaryDigit( int ch )
{
    return ch == '0' || ch == '1';
}

/**
    Parses binary expressions with "or"
    @param *input FILE pointer to input file.
    @return left Expr *left pointer to new parsed expression
*/
Expr *parseOrExpr(FILE *input)
{
    Expr *left = parseXorExpr( input );

    while ( peek( input ) == '|' ) {
        match( input, "|" );
        Expr *right = parseXorExpr( input );
        left = makeOrExpr( left, right );
    }

    return left;
}

/**
    Parses binary expressions with "^" (Xor)
    @param *input FILE pointer to input file.
    @return left Expr *left pointer to new parsed expression
*/
Expr *parseXorExpr(FILE *input)
{
    Expr *left = parseAndExpr( input );

    while ( peek( input ) == '^' ) {
        match( input, "^" );
        Expr *right = parseAndExpr( input );
        left = makeXorExpr( left, right );
    }

    return left;
}

/**
    Parses binary expressions with "&" (And)
    @param *input FILE pointer to input file.
    @return left Expr *left pointer to new parsed expression
*/
Expr *parseAndExpr(FILE *input)
{
    Expr *left = parseShiftExpr( input );

    while ( peek( input ) == '&' ) {
        match( input, "&" );
        Expr *right = parseShiftExpr( input );
        left = makeAndExpr( left, right );
    }

    return left;
}

/** =
    Parse either a left shift or a right shift expression, a sequence
    of one or more higher-precedence subexpressions separated by << or
    >>.
    @param input stream to parse the expression from
    @return new expression parsed.
*/
Expr *parseShiftExpr( FILE *input )
{
    Expr *left = parseComplementExpr( input );

    while ( peek( input ) == '<' || peek( input ) == '>' ) {
        // Build the proper shift expression, based on
        // the one-character look-ahead.
        if ( peek( input ) == '<' ) {
            match( input, "<<" );
            Expr *right = parseComplementExpr( input );
            left = makeShiftLeftExpr( left, right );
        } else {
            match( input, ">>" );
            Expr *right = parseComplementExpr( input );
            left = makeShiftRightExpr( left, right );
        }
    }

    return left;
}

/**
    Parse a conplement (~) expression
    @param input stream to parse the expression from
    @return new expression parsed.
*/
Expr *parseComplementExpr( FILE *input )
{
    Expr *result;
    Expr *next;

    if ( peek( input ) == '~' ) {
        match( input, "~" );
        next = parseComplementExpr( input );
        result = makeComplementExpr( next );
        return result;
    } else {
        result = parseAtomicExpr( input );
        return result;
    }
    

}

/**
    Parse either a binary value or an expression wrapped in parentheses.
    @param input stream to parse the expression from
    @return new expression parsed.
*/
Expr *parseAtomicExpr( FILE *input )
{
    int ch = peek( input );

    if ( isBinaryDigit( ch ) ) {
        // For now, just skip a sequence of bits and
        // just parse everything as a fixed, 16-bit value.
        int length = 1;
        int count = 0;
        char *binStr = calloc(length, sizeof(char));
        while ( isBinaryDigit( ch = fgetc( input ) ) ) {
            if (count+1 > length) {
                length *= 2;
                binStr = realloc(binStr, length*sizeof(char));
            }
            binStr[count] = ch;
            count++;
        }
        if ( ch != EOF )
            ungetc( ch, input );
        if (count >= length) {
            binStr = realloc(binStr, (length+1)*sizeof(char));
        }
        binStr[count] = '\0';

        Binary *val = stringToBinary( binStr );
        Expr *expr = makeValueExpr( val );
        free(binStr);
        return expr;
    } else if ( ch == '(' ) {

        match( input, "(");
        Expr *inside = parseOrExpr( input );

        if ( peek( input ) == ')' ) {
            match( input, ")" );
        } else {
            if ( peek( input ) == ';') {
                printf("Unexpected character ';' on line %d\n", linenum);
            }
            exit(EXIT_FAILURE);
        }

        return inside;
    }

    printf( "Unexpected character '%c' on line %d\n", ch, linenum );
    exit( EXIT_FAILURE );
}


/**
    Parse, evaluate and print the value of a sequence of boolean
    expression read from standard input.
    @param argc number of command-line arguments
    @param argv list of command-line arguments

    @return program exit status
*/
int main( int argc, char *argv[] )
{
    FILE *input;
    if (argc > 2) {
        printf("usage: interpreter [program-file]");
        return EXIT_FAILURE;
    }
    if (argc > 1) {
        input = fopen(argv[1], "r");
        if (input == NULL) {
            printf("Can't open input file: %s\n", argv[1]);
            return EXIT_FAILURE;
        }
    } else {
        input = stdin;
    }
    // Result of each expression, reused for each expressions since it
    // just gets overwritten anyway.
    Binary *val = makeBinary( DEFAULT_BINARY_LEN );

    while ( peek( input ) != EOF ) {
        Expr *expr = parseOrExpr( input );
        match( input, ";" );
        expr->eval( expr, val );
        
        char *str = binaryToString( val );
        printf( "%s\n", str );

        // Free expression and string result for this program.
        expr->destroy( expr );
        free( str );
    }

    freeBinary( val );
    fclose (input);
    return EXIT_SUCCESS;
}
