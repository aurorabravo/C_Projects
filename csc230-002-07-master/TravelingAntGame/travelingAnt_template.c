#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
   //The number of command line arguments is stored in argc.
   //The command line arguments are stored in argv, which is an
   //array of strings (where each string is a char * type).
   //The executable is always the value stored in argv[0].

   //There should always be a check for the right number of
   //command line arguments.
   File *antFile;
   if (argc != 2) {
      printf("Usage: ./travelingAnt <flagstone-file>\n");
      exit(EXIT_FAILURE);
   }

   antFile = fopen(argv[1], "r");
   if (antFile == NULL) {
      printf("Cannot read file.\n");
      exit(EXIT_FAILURE);
   }


   //The filename is stored in argv[1].  It's type is a 
   //char *, which is appropriate to use in fopen().

   return EXIT_SUCCESS;
}
