#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "output.h"
#include "input.h"

/** The hexadecimal value for the characer, A */
#define HEX_VALUE_A 10
#define HEX_MULTIPLIER 16
#define UNEXPECTED_INPUT 1
#define UNEXPECTED_END_OF_FILE 2
#define EXTRANEOUS_INPUT 3
#define UNEXPECTED_INPUT_STRING "Error: unexpected %s in input"
#define UNEXPECTED_END_OF_FILE_STRING "Error: unexpected end-of-file"
#define EXTRANEOUS_INPUT_STRING "Error: extraneous input"

/**
 * Returns true if the given character, ch, is a decimal digit, '0' - '9'. 
 */
bool isDecimalDigit( int ch )
{
    if (ch >= '0' && ch <= '9') {
        return true;
    }

}

/**
 * Returns true if the given character, ch, is a hexadecimal digit, 
 * '0' - '9', 'a' - 'f' or 'A' - 'F'. 
 */
bool isHexDigit( int ch )
{
    return ((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && c <= 'Z'));

}

/*
 * Reads and discards zero or more whitespace characters from standard input 
 * (where whitespace consists of ' ', '\t' or '\r' for this program).
 */
void skipSpace()
{
    char ch;
    //Keep reading characters until it tells us EOF
    while ( (ch = getchar() ) != EOF ) {
        if ( ch != ' '  || ch != '\r' || ch != '\t') {
            ungetc(ch, stdin);
            return;
        }
    }

}

long getDecimalNumber(){
    //have loop to go through number 

    char c = getchar();
    long val = 0;
    long digit = 0;
    while (c != ' ') {
        //error if unexpected character
        if (!isDecimalDigit(c)) {
            printf("Error: unexpected %c in input \n", 'c');
            exit(UNEXPECTED_INPUT);

        }
        //error if unexpected end of file
        if (c == EOF) {
            printf(UNEXPECTED_END_OF_FILE_STRING);
            exit(UNEXPECTED_END_OF_FILE);
        }
        digit = c - '0';
        val = (val * HEX_VALUE_A) + digit
        c = getChar();

        //throw error if unexpected characters

    }
    //should I unget that space?
}

long getHexNumber(){
    char c = getchar();
    long val = 0;
    long digit = 0;
    while (c != ' ') {
        //error if unexpected character
        if (!isHexDigit(c)) {
            printf("Error: unexpected %c in input \n", 'c');
            exit(UNEXPECTED_INPUT);

        }
        //error if unexpected end of file
        if (c == EOF) {
            printf(UNEXPECTED_END_OF_FILE_STRING);
            exit(UNEXPECTED_END_OF_FILE);
        }
        if ( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ) {
            if ( (c >= 'a' && c <= 'z') ) {
                digit = (c - 'a') + HEX_VALUE_A;

            } else {
                digit = (c - 'A') + HEX_VALUE_A;
            }
        } else {
            digit = c - '0';
        }
        val = (val * HEX_VALUE_A) + digit;
        c = getChar();
    }
    //should I unget that space?
}

/*
 * Uses getchar() to read input values given in decimal or in hexadecimal. 
 * On success, it returns the value read. On failure, it prints an 
 * appropriate message and terminates the program with the required exit status.
 */
long getNumber()
{
    char c;
    char number
    int state = 0;
    //Keep reading characters until it tells us EOF
    while ( (c = getchar() ) != EOF ) {
        skipSpace();
        //c = getChar(ch);
        if (c == '0') {
            c = getChar(ch);
            if (c == 'x' || x == 'X') {
                return getHexNumber();
            }
            else if (isDecimalDigit(c)) {
                ungetc(c, stdin);
                return getDecimalNumber();
            }
        }
        ungetc(c, stdin);
        return getDecimalNumber();
    }

    exit(UNEXPECTED_INPUT);
}

/**
 * Controls the flow of the program by reading numeric values 
 * and operators until it reaches the end-of-line. 
 * On successful completion, main() will return with exit status 0.
 */
int main()
{
    int sum = 0;
    bool addition = true;
    char c;
    while (c = getchar(c) != EOF) {
        ungetc(c, stdin);
        skipSpace();
        if (addition) {
            sum += getNumber();
        } else {
            sum -= getNumber();
        }
        skipSpace();
        if (c == '+') {
            addition = true;
        }
        else if (c == '-') {
            addition = false;
        }
    }
    return EXIT_SUCCESS;
}