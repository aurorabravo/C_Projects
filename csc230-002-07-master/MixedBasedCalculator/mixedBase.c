#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/** 
    @file mixedBase.c
    @author Aurora Bravo (aibravoe@ncsu.edu)

    Takes in a file with a sum of numbers in decimal and hexadecimal
    and returns the output in decimal

*/

/** The hexadecimal value for the characer, A */
#define HEX_VALUE_A 10
/** The hexadecimal multiplier */
#define HEX_MULTIPLIER 16
/** Exit value for unexpected input */
#define UNEXPECTED_INPUT 1
/** Exit value for unexpected end of file */
#define UNEXPECTED_END_OF_FILE 2
/** Exit value for extraneous input */
#define EXTRANEOUS_INPUT 3
/** String for unexpected input message */
#define UNEXPECTED_INPUT_STRING "Error: unexpected '%c' in input.\n"
/** String for unexpected end of file message */
#define UNEXPECTED_END_OF_FILE_STRING "Error: unexpected end-of-file.\n"
/** String for uextraneous input message */
#define EXTRANEOUS_INPUT_STRING "Error: extraneous input.\n"
/** Global boolean variable for found line feed */
bool found_lf = false;

/**
 * Returns true if the given character, ch, is a decimal digit, '0' - '9'. 
 * @param ch int character
 */
bool isDecimalDigit( int ch )
{
    return (ch >= '0' && ch <= '9');
}

/**
 * Returns true if the given character, ch, is a hexadecimal digit, 
 * '0' - '9', 'a' - 'f' or 'A' - 'F'. 
 * @param ch int character
 */
bool isHexDigit( int ch )
{
    return ((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'f') || (ch >= 'A' && ch <= 'F'));

}

/*
 * Reads and discards zero or more whitespace characters from standard input 
 * (where whitespace consists of ' ', '\t' or '\r' for this program).
 */
void skipSpace()
{
    char ch;
    //Keep reading characters until it tells us EOF
    while ( 1 ) {
        ch = getchar();
        if (ch == EOF ) { 
            break; 
        }
        if ( ch != ' '  && ch != '\r' && ch != '\t' && ch != '\n') {
            ungetc(ch, stdin);
            return;
        }
    }

}

/*
 * Returns decimal number
 * @return val long decimal number
 */
long getDecimalNumber(){
    //have loop to go through number 

    char c = getchar();
    long val = 0;
    long digit = 0;
    //printf("Character before loop in decimal '%c' \n", c);
    while (c != ' '  && c != '\r' && c != '\t' && c != HEX_VALUE_A && c != '+' && c != '-') {

        //error if unexpected end of file
        if (c == EOF) {
            printf(UNEXPECTED_END_OF_FILE_STRING);
            exit(UNEXPECTED_END_OF_FILE);
        }
        //error if unexpected character
        if (!isDecimalDigit(c)) {
            printf(UNEXPECTED_INPUT_STRING, c);
            exit(UNEXPECTED_INPUT);

        }
        digit = c - '0';
        val = (val * HEX_VALUE_A) + digit;
        c = getchar();

        //throw error if unexpected characters

    }
    if (c == HEX_VALUE_A) {
        found_lf = true;
    } else if (found_lf) {
        printf(EXTRANEOUS_INPUT_STRING);
        exit(EXTRANEOUS_INPUT);
    }
    ungetc(c, stdin);
    skipSpace();
    //printf("Character after loop in getdecmial '%c' \n", c);
   //ungetc(c, stdin);
    //printf("Value of Decimal: '%ld' \n", val);
    //should I unget that space?
    return val;
}

/**
 * Returns hex number
 * @return val long hex number
 */
long getHexNumber(){
    char c = getchar();
    //printf("Character in getHexNumber '%c' \n", c);
    long val = 0;
    long digit = 0;
    while (c != ' '  && c != '\r' && c != '\t' && c != HEX_VALUE_A && c != '+' && c != '-') {
        //printf("Character in getHexNumber loop '%c' \n", c);
        //error if unexpected end of file
        if (c == EOF) {
            printf(UNEXPECTED_END_OF_FILE_STRING);
            exit(UNEXPECTED_END_OF_FILE);
        }
        //error if unexpected character
        if (!isHexDigit(c)) {
            //printf("Error: unexpected '%c' in input \n", c);
            exit(UNEXPECTED_INPUT);

        }
        if ( (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F') ) {
            if ( (c >= 'a' && c <= 'f') ) {
                digit = (c - 'a') + HEX_VALUE_A;

            } else {
                digit = (c - 'A') + HEX_VALUE_A;
            }
        } else {
            digit = c - '0';
        }
        val = (val * HEX_MULTIPLIER) + digit;
        c = getchar();
    }
    if (c == HEX_VALUE_A ) {
        found_lf = true;
    } else if (found_lf) {
        printf(EXTRANEOUS_INPUT_STRING);
        exit(EXTRANEOUS_INPUT);
    }
        
    //should I unget that space?
    ungetc(c, stdin);
    return val;
}

/*
 * Uses getchar() to read input values given in decimal or in hexadecimal. 
 * On success, it returns the value read. On failure, it prints an 
 * appropriate message and terminates the program with the required exit status.
 */
long getNumber()
{
    char c = getchar();
    long number = 0;
    while ( c  != EOF ) {
        //printf("Character in getNumber() before if '%c' \n", c);
        //ungetc(c, stdin);
        //printf("Character in getNumber() before if '%c' \n", c);
        skipSpace();
        //printf("Character in getNumber() after skipspace '%c' \n", c);
        if (c == '0') {
            c = getchar();
            //printf("Character in getNumber() after 0 '%c' \n", c);
            if (c == 'x' || c == 'X') {
                return getHexNumber();
            }
            else if (isDecimalDigit(c)) {
                ungetc(c, stdin);
                //printf("Character in getNumber() decimal '%c' \n", c);
                return getDecimalNumber();
            }
        }
        //skipSpace();
        ungetc(c, stdin);
        //ungetc(c, stdin);
        //skipSpace();
        //printf("Character in getNumber() not starting with 0: '%c' \n", c);
        return getDecimalNumber();
    }
    //exit(EXTRANEOUS_INPUT);
    return number;
    //exit(UNEXPECTED_INPUT);
}

/**
 * Controls the flow of the program by reading numeric values 
 * and operators until it reaches the end-of-line. 
 * On successful completion, main() will return with exit status 0.
 */
int main()
{
    long sum = 0;
    bool addition = true;
    char c;
    //ungetc(c, stdin);
    //printf("Character before loop in main '%c' \n ", c);
    while (1) {
        c = getchar();
        if (c == EOF) { 
            break; 
        }
        if (c == HEX_VALUE_A) {
            found_lf = true;
        } else if (found_lf) {
            printf(EXTRANEOUS_INPUT_STRING);
            exit(EXTRANEOUS_INPUT);
        }
        ungetc(c, stdin);
        //printf("Character in loop in main '%c' \n ", c);

        skipSpace();
        c = getchar();
        //printf("Character after skip space '%c' \n", c);
        ungetc(c, stdin);
        if (c == '+') {
            addition = true;
            getchar();
            //skipSpace();
        }
        else if (c == '-') {
            addition = false;
            getchar();
            //skipSpace();
        }
        else if (isHexDigit(c)) {
            if (addition) {
                //ungetc(c, stdin); //test   
                //skipSpace();
                sum += getNumber();
                //printf("Sum is: %ld \n ", sum);
                //skipSpace();
                //c=getchar();
            } else {
                //ungetc(c, stdin); //test
                sum -= getNumber();
                //printf("- Sum is: %ld \n ", sum);
                //skipSpace();
                //c=getchar();
            }
        } else {
            printf(UNEXPECTED_INPUT_STRING, c);
            exit(UNEXPECTED_INPUT);
        }
        skipSpace();
        //c = getchar();
        //if (c == '+' || c == '-'){
        //    ungetc(c, stdin);
        //}
    }
    //printf("Sum at end is: %ld \n ", sum);
    printf("%ld\n", sum);
    return EXIT_SUCCESS;
}
